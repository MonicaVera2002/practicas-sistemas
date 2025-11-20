int tempPin = A0;
int ldrPin  = A1;
int humDig  = 4;
int tapPin  = 2;

// Clave XOR de 1 byte (puedes cambiarla)
const byte XOR_KEY = 0x5A;  

void setup() {
  Serial.begin(9600);

  pinMode(humDig, INPUT);
  pinMode(tapPin, INPUT_PULLUP);
}

void sendXOR(String data) {
  for (int i = 0; i < data.length(); i++) {
    byte c = data[i] ^ XOR_KEY;
    Serial.write(c);
  }
  Serial.write('\n'); // separador de línea
}

void loop() {
  int tempVal = analogRead(tempPin);
  float tempC = (tempVal * 5.0 / 1023.0) * 10;

  int luzVal = analogRead(ldrPin);
  int humD = digitalRead(humDig);
  int tap = digitalRead(tapPin);

  // Empaquetamos en un solo string
  String packet = "";
  packet += "T:" + String(tempC) + ";";
  packet += "L:" + String(luzVal) + ";";
  packet += "HD:" + String(humD) + ";";
  packet += "G:" + String(tap);

  // Enviar cifrado
  sendXOR(packet);

  delay(500);
}




