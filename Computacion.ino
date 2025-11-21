int tempPin = A0;
int ldrPin  = A1;
int humDig  = 4;
int tapPin  = 2;

// Genera la llave XOR
byte llave = 0b11001100;

// Se cifran los datos generados por los sensores
String cifrarBinario(String mensaje) {
  String binario = "";
  for (int i = 0; i < mensaje.length(); i++) {
    char cifrado = mensaje[i] ^ llave;
    for (int b = 7; b >= 0; b--) {
      binario += bitRead(cifrado, b) ? '1' : '0';
    }
    binario += ' ';
  }
  return binario;
}


void setup() {
  Serial.begin(9600);

  pinMode(humDig, INPUT);
  pinMode(tapPin, INPUT_PULLUP);
}

void loop() {
  int tempVal = analogRead(tempPin);
  float tempC = (tempVal * 5.0 / 1023.0) * 10;

  // Se recolectan todos los datos como enteros
  int luzVal = analogRead(ldrPin);
  int humD = digitalRead(humDig);
  int tap = digitalRead(tapPin);

  // Se juntan todos los datos dentro de un String
  String packet = "";
  packet += "T:" + String(tempC) + ";";
  packet += "L:" + String(luzVal) + ";";
  packet += "HD:" + String(humD) + ";";
  packet += "G:" + String(tap);

  // Se cifran los datos en binario dentro de un pequeño paquete
  String cifrado = cifrarBinario(packet);

  // Envían los datos cifrados a la Raspberry
  Serial.println(cifrado);

  delay(1000);
}




