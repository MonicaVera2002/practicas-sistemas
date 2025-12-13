// Nombramos los sensores y sus pines
const int lm35 = A0;
const int ky038 = A2;
const int mq2 = 3;
const int sw420 = 4;
const int pir = 2;

// Activan los LEDs y los Buzzerse
int LAlerta = 13;
int LSiempre = 12;
int TLNormal = 11;

int BNaranja = 9; 
int BAzul = 7;   
int BVerde = 8;   
int BMorado = 6;  

//Cifrar con XOR
int sonido = 30;
byte codXOR = 0x5A;

//CIFRADO
byte xorByte(byte b, byte llave) {
  return b ^ llave;
}

// ======= FIX: SIEMPRE 8 bits =======
String formar8bits(byte c) {
  String bin = String(c, BIN);
  while (bin.length() < 8) bin = "0" + bin;
  return bin;
}

String cifrarEnteroBin(int numero, byte llave) {
  byte cif = numero ^ llave;
  return formar8bits(cif);
}

// ======= FIX: CADA CARACTER SE ENVÍA EN 8 bits =======
String cifrarMensaje(String msg, byte llave) {
  String mensaje = "";
  for (int i = 0; i < msg.length(); i++) {
    byte c = xorByte((byte)msg[i], llave);
    mensaje += formar8bits(c);
    if (i < msg.length() - 1) mensaje += " ";
  }
  return mensaje;
}

void setup() {
  Serial.begin(9600);

  pinMode(LAlerta, OUTPUT);
  pinMode(LSiempre, OUTPUT);
  pinMode(TLNormal, OUTPUT);

  pinMode(BNaranja, OUTPUT);
  pinMode(BAzul, OUTPUT);
  pinMode(BVerde, OUTPUT);
  pinMode(BMorado, OUTPUT);

  pinMode(mq2, INPUT);
  pinMode(sw420, INPUT);
  pinMode(pir, INPUT);

  digitalWrite(LSiempre, HIGH);
}

void loop() {

  int lecturaLM = analogRead(lm35);
  float mv = (lecturaLM * 500.0) / 1023.0;
  float temperaturaFloat = mv * 0.1; // Si tu LM35 está calibrado así

  // Convertimos la temperatura a texto
  String temperaturaString = String(temperaturaFloat, 2);

  int valorSonido = analogRead(ky038);
  int estadoMQ2 = digitalRead(mq2);
  int estadoSW420 = digitalRead(sw420);
  int estadoPIR = digitalRead(pir);

  String msjTemp;
  String msjMQ2;
  String msjKY;
  String msjSW;
  String msjPIR;

  bool alerta = false;
  bool tempNormal = false;

  if (temperaturaFloat > 35) { msjTemp = "ALERTA: Temperatur alta"; alerta = true; }
  else if (temperaturaFloat < 30) { msjTemp = "ALERTA: Temperperatura baja"; alerta = true; }
  else { msjTemp = "Temperatura normal"; tempNormal = true; }

  if (estadoMQ2 == LOW) { msjMQ2 = "ALERTA: Fuga de Gas"; alerta = true; tone(BAzul, 800, 300); }
  else { msjMQ2 = "Sin gas detectado"; noTone(BAzul); }

  if (valorSonido > sonido) { msjKY = "ALERTA: Sonido Inusual"; alerta = true; tone(BVerde, 1200, 150); }
  else { msjKY = "Estado: Normal"; noTone(BVerde); }

  if (estadoSW420 ==  HIGH) { msjSW = "ALERTA: Temblor"; alerta = true; tone(BMorado, 3000, 100); }
  else { msjSW = "Estado: Normal"; noTone(BMorado); }

  if (estadoPIR == LOW) { msjPIR = "ALERTA: Movimiento detectado!"; alerta = true; tone(BNaranja, 900, 400); }
  else { msjPIR = "Sin movimiento"; noTone(BNaranja); }

  if (alerta) {
    digitalWrite(LAlerta, HIGH);
    digitalWrite(LSiempre, LOW);
    digitalWrite(TLNormal, LOW);
  } else {
    digitalWrite(LAlerta, LOW);
    digitalWrite(LSiempre, HIGH);
    digitalWrite(TLNormal, tempNormal ? HIGH : LOW);
  }

  Serial.println("CONTROL");

  Serial.println(cifrarMensaje(temperaturaString, codXOR));
  Serial.println(cifrarEnteroBin(estadoMQ2, codXOR));
  Serial.println(cifrarEnteroBin(valorSonido, codXOR));
  Serial.println(cifrarEnteroBin(estadoSW420, codXOR));
  Serial.println(cifrarEnteroBin(estadoPIR, codXOR));

  Serial.println(cifrarMensaje(msjTemp, codXOR));
  Serial.println(cifrarMensaje(msjMQ2, codXOR));
  Serial.println(cifrarMensaje(msjKY, codXOR));
  Serial.println(cifrarMensaje(msjSW, codXOR));
  Serial.println(cifrarMensaje(msjPIR, codXOR));

  Serial.println("FIN DEL CONTROL");

  delay(1000);
}






