int mq2 = 8;        // Pin DO del MQ-2
int ledGas = 13;    // LED que se activa con gas
int buzzer = 7;     // Buzzer
int ledFijo = 12;   // LED siempre encendido

void setup() {
  Serial.begin(9600);

  pinMode(mq2, INPUT);
  pinMode(ledGas, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledFijo, OUTPUT);

  digitalWrite(ledFijo, HIGH); // LED 12 siempre encendido
  digitalWrite(ledGas, LOW);   // LED 13 apagado inicialmente
}

void loop() {
  int estado = digitalRead(mq2);

  // En MQ-2: LOW = gas detectado
  if (estado == HIGH) {
    digitalWrite(ledGas, HIGH);
    digitalWrite(ledFijo, LOW);
    tone(buzzer, 800, 300);  
    Serial.println("ALERTA: Detectado GAS / HUMO (MQ-2)");
  } 
  else {
    digitalWrite(ledGas, LOW);
    digitalWrite(ledFijo, HIGH);
    noTone(buzzer);
    Serial.println("Sin gas detectado");
  }

  delay(1000);
}
