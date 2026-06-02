const int sensorPin = 9;
int lastState = HIGH;  // Empieza en HIGH porque sin obstáculo, el sensor da HIGH

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int currentState = digitalRead(sensorPin);

  // Detecta cambio de HIGH a LOW (obstáculo aparece)
  if (currentState == LOW && lastState == HIGH) {
    Serial.println("Obstáculo detectado");
  }

  // Detecta cambio de LOW a HIGH (obstáculo se va)
  if (currentState == HIGH && lastState == LOW) {
    Serial.println("Obstáculo retirado");
  }

  // Actualiza el estado anterior
  lastState = currentState;

  delay(100);
}

