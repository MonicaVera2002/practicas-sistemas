int sw420 = 4;      // Sensor SW-420
int ledMov = 13;    // LED que se activa al detectar vibración
int buzzer = 7;     // Buzzer
int ledFijo = 12;   // LED siempre encendido

void setup() {
  Serial.begin(9600);

  pinMode(sw420, INPUT);
  pinMode(ledMov, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledFijo, OUTPUT);

  digitalWrite(ledFijo, HIGH);  // LED 12 encendido siempre
  digitalWrite(ledMov, LOW);    // LED 13 apagado inicialmente
}

void loop() {
  int estado = digitalRead(sw420);

  // Ojo: en SW-420 LOW = vibración detectada
  if (estado == LOW) {
    digitalWrite(ledMov, HIGH);
    digitalWrite(ledFijo, LOW);
    tone(buzzer, 3000,100);
    Serial.println("ALERTA: ¡Vibración detectada (SW-420)!");
  } 
  else {
    digitalWrite(ledMov, LOW);
    digitalWrite(ledFijo,HIGH);
    noTone(buzzer);
    Serial.println("Sin vibraciones, ambiente estable.");
  }

  delay(3000);  // delay corto para mejorar la detección
}
