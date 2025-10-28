#include <SoftwareSerial.h>

// --- Definición de pines para los sensores ---
int temperature = A0;   
int photoresistor = A1;  
int proximity = 9; 
  

// --- Variables para el estado del FC-51 ---
int lastState = HIGH;  // Empieza en HIGH porque sin obstáculo el sensor da HIGH

// --- Configuración del módulo HC-05 ---
int rx = 2;   // RX del Arduino (conectar al TX del HC-05)
int tx = 3;   // TX del Arduino (conectar al RX del HC-05)
SoftwareSerial BT(rx, tx); // Comunicación Bluetooth

void setup() {
  Serial.begin(9600);   // Comunicación con el monitor serial
  BT.begin(9600);       // Comunicación con el HC-05 (velocidad por defecto)

  pinMode(proximity, INPUT);

  Serial.println("Waiting for data.");
  BT.println("Waiting for data.");
}

void loop() {
  // ---- Lectura del sensor LM35 ----
  int analogTemperature = analogRead(temperature);
  float voltage = (analogTemperature / 1023.0) * 5000;  // en milivoltios
  float temperatureC = voltage / 100;  // Cada 10 mV equivale a 1 °C

  // ---- Lectura del sensor KY-018 ----
  int analogPhotoresistor = analogRead(photoresistor);

  // ---- Lectura del sensor FC-51 ----
  int currentState = digitalRead(proximity);

  // ---- Construir mensaje ----
  String message = "Temperature: " + String(temperatureC, 1) + " °C | Brightness: " + String(analogPhotoresistor) + " | Movement: ";

  if (currentState == LOW && lastState == HIGH) {
    message += " Detected!!";
  } else if (currentState == HIGH && lastState == LOW) {
    message += " Removed!!";
  } else {
    message += " Unchanged.";
  }

  // ---- Mostrar datos en el monitor serial y enviarlos por Bluetooth ----
  Serial.println(message);
  BT.println(message);

  // ---- Actualiza el estado anterior ----
  lastState = currentState;

  delay(4000);
}
