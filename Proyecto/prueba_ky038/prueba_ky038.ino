int sensor = A2;       
int ledEstado = 12;
int ledAlerta = 13;
int buzzer = 7;

int umbralRuido = 35;   // Ajusta después de medir
byte claveXOR = 0x5A;


// --- Cifra un número entero y lo devuelve como binario ---
String cifrarEnteroBin(int numero, byte clave) {
  int cifrado = numero ^ clave;         // XOR
  return String(cifrado, BIN);          // binario
}


// --- Cifra un mensaje completo carácter por carácter ---
String cifrarMensaje(String msg, byte clave) {
  String salida = "";
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i] ^ clave;            // XOR por caracter
    salida += String(c, BIN) + " ";     // convertir a binario
  }
  return salida;
}


void setup() {
  Serial.begin(9600);

  pinMode(ledEstado, OUTPUT);
  pinMode(ledAlerta, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(ledEstado, HIGH);
  digitalWrite(ledAlerta, LOW);
}


void loop() {
  int valor = analogRead(sensor);

  // --- Cifrar valor del sensor ---
  String valorCifrado = cifrarEnteroBin(valor, claveXOR);

  // --- Decidir mensaje ---
  String msg;

  if (valor > umbralRuido) {
    digitalWrite(ledAlerta, HIGH);
    tone(buzzer, 1200, 150);
    delay(200);
    msg = "ALERTA: Sonido Inusual";
  } 
  else {
    digitalWrite(ledAlerta, LOW);
    noTone(buzzer);
    msg = "Todo normal";
  }

  // --- Cifrar mensaje ---
  String msgCifrado = cifrarMensaje(msg, claveXOR);

  // --- Enviar todo ---
  Serial.println(valor);
  Serial.print("Valor cifrado: ");
  Serial.println(valorCifrado);

  Serial.print("Mensaje cifrado: ");
  Serial.println(msgCifrado);

  delay(700);
}

