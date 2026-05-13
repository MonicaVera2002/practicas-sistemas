int sensorTemp = A0;   // Sensor LM35 en A0
int ledCalor = 13;     // Temperatura > 40°C
int ledFrio = 12;      // Temperatura < 20°C
int ledNormal = 11;    // Temperatura entre 20°C y 40°C

void setup() {
  Serial.begin(9600);

  pinMode(ledCalor, OUTPUT);
  pinMode(ledFrio, OUTPUT);
  pinMode(ledNormal, OUTPUT);
}

void loop() {
  int lectura = analogRead(sensorTemp);

  // Conversión del LM35: 10mV por °C
  float milivoltios = (lectura * 5000.0) / 1023.0;
  float temperatura = milivoltios / 100.0;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  // Lógica de control de LEDs
  if (temperatura > 40) {
    digitalWrite(ledCalor, HIGH);   // Calor
    digitalWrite(ledFrio, LOW);
    digitalWrite(ledNormal, LOW);
  }
  else if (temperatura < 20) {
    digitalWrite(ledFrio, HIGH);    // Frío
    digitalWrite(ledCalor, LOW);
    digitalWrite(ledNormal, LOW);
  }
  else {
    // Entre 20 y 30
    digitalWrite(ledNormal, HIGH);  // Rango normal
    digitalWrite(ledCalor, LOW);
    digitalWrite(ledFrio, LOW);
  }

  delay(500);
}


