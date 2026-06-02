#include <SoftwareSerial.h>

// --- Declaramos las variables----
int temperature = A0;
int photoresistor = A1;
int proximity = 9;
int lastState = HIGH;
int rx = 2;
int tx = 3;
SoftwareSerial BT(rx, tx); // RX=2, TX=3

// ---Declaramos la llave XOR---
byte llave = 0b11001100;


String cifrarBinario(String mensaje);
String descifrarBinario(String mensajeBinario);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(proximity, INPUT);

  Serial.println("Bluetooth y Serial listos: cifrado en binario + mensaje descifrado.");
  BT.println("Bluetooth listo: cifrado en binario + mensaje descifrado.");
}

void loop() {
  // ---- Se realiza la lectura de los sensores ----
  int analogTemperature = analogRead(temperature);
  float voltage = (analogTemperature / 1023.0) * 5000;
  float temperatureC = voltage / 100.0;
  int analogPhotoresistor = analogRead(photoresistor);
  int currentState = digitalRead(proximity);

  // ---- Mensaje de los datos de los sensores ----
  String message = "Temp: " + String(temperatureC, 1) +
                   " °C | Luz: " + String(analogPhotoresistor) +
                   " | Movimiento: ";

  if (currentState == LOW && lastState == HIGH) {
    message += "Detectado!";
  } else if (currentState == HIGH && lastState == LOW) {
    message += "Removido!";
  } else {
    message += "Sin cambios.";
  }

  // ---- Cifrar mensaje en binario ----
  String cifrado = cifrarBinario(message);

  // ---- Descifrar (desde binario) ----
  String descifrado = descifrarBinario(cifrado);

  // ---- Enviamos información a la terminal de Arduino ----
  Serial.println("---------------------------");
  Serial.println("Mensaje original:");
  Serial.println(message);
  Serial.println("Mensaje cifrado (binario):");
  Serial.println(cifrado);
  Serial.println("Mensaje descifrado:");
  Serial.println(descifrado);

  // ---- Enviamos el mensaje a Bluetooth ----
  BT.println("---------------------------");
  BT.println("Mensaje cifrado (binario):");
  BT.println(cifrado);
  BT.println("Mensaje descifrado:");
  BT.println(descifrado);

  lastState = currentState;
  delay(4000);
}

// ======================================================
// Cifrar mensaje en binario con XOR
// ======================================================
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

// ======================================================
// Descifrar mensaje binario (inverso del anterior)
// ======================================================
String descifrarBinario(String mensajeBinario) {
  String texto = "";
  for (int i = 0; i < mensajeBinario.length(); i += 9) { 
    byte valor = 0;
    for (int b = 0; b < 8; b++) {
      if (mensajeBinario[i + b] == '1') {
        bitWrite(valor, 7 - b, 1);
      }
    }
    //Aplicamos XOR para decifrar
    char descifrado = valor ^ llave; 
    texto += descifrado;
  }
  return texto;
}


