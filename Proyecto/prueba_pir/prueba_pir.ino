int pir = 2;        // Sensor PIR
int ledMov = 13;    // LED que se activa con movimiento
int buzzer = 5;     // Buzzer
int ledFijo = 12;   // LED que siempre está encendido

void setup() {
  Serial.begin(9600);

  pinMode(pir, INPUT);
  pinMode(ledMov, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledFijo, OUTPUT);

  digitalWrite(ledFijo, HIGH);   // LED 12 siempre encendido
  digitalWrite(ledMov, LOW);     // LED movimiento inicialmente apagado
}

void loop() {
  int estado = digitalRead(pir);

  if (estado == HIGH) {
    digitalWrite(ledMov, HIGH);
    digitalWrite(ledFijo, LOW);
    tone(buzzer, 800,300);  
    Serial.println("ALERTA: Movimiento detectado!");
  } 
  else {
    digitalWrite(ledMov, LOW);
    digitalWrite(ledFijo, HIGH);
    noTone(buzzer);
    Serial.println("Sin movimiento detectado, actividad normal");
  }

  delay(1000); // puedes ajustar el tiempo
}

