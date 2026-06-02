#include <SoftwareSerial.h>
SoftwareSerial canal (10, 11); // RX=8, TX=9

#define XOR_KEY 42

const int pinLM35 = A0;
const int pinLDR = A2;
const int pinProx = 2;

String xorCipher(String texto) {
  String resultado = "";
  for (int i = 0; i < texto.length(); i++) {
    resultado += char(texto[i] ^ XOR_KEY);
  }
  return resultado;
}

void setup() {
  Serial.begin(9600);
  canal.begin(4800);
  pinMode(pinProx, INPUT);
  Serial.println("=== Arduino B listo ===");
}

String leerSensores() {
  int valorLM35 = analogRead(pinLM35);
  float temperatura = (valorLM35 * 5.0 / 1023.0) * 100.0;
  int valorLDR = analogRead(pinLDR);
  int valorProx = digitalRead(pinProx);

  char buffer[50];
  snprintf(buffer, sizeof(buffer), "T=%f,L=%d,P=%d", temperatura, valorLDR, valorProx);
  return String(buffer);
}

String recibirMensaje() {
  String recibido = "";
  unsigned long t0 = millis();
  while (millis() - t0 < 1500) {
    while (canal.available()) {
      char c = canal.read();
      if (c == '\n') return recibido;
      recibido += c;
    }
  }
  return recibido;
}

void loop() {
  String recibidoCifrado = recibirMensaje();
  if (recibidoCifrado.length() > 0) {
    Serial.println("Recibido cifrado de A: " + recibidoCifrado);
    String descifrado = xorCipher(recibidoCifrado);
    Serial.println("Descifrado (sensores de A): " + descifrado);

    String datosLocales = leerSensores();
    Serial.println("Datos locales: " + datosLocales);

    String cifrado = xorCipher(datosLocales);
    canal.println(cifrado);
    Serial.println("Datos cifrados enviados: " + cifrado);
    Serial.println("-------------------------------");
  }
}






















