const int analogPin = A0; // Define el pin del sensor analógico

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(analogPin); // Lee el valor del sensor analógico
  Serial.print("Raw value: ");
  Serial.println(rawValue);
  
 }
