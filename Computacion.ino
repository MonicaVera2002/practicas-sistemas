int temperature = A0;
int photoresistor = A1;
int proximity = 8;
int tap = 12;                 
int lastState = HIGH;

// Se crea la llave XOR
byte llave = 0b11001100;

String cifrarBinario(String mensaje);
String descifrarBinario(String mensajeBinario);

// Comenzamos con la comunicación serial
void setup() {
  Serial.begin(9600);   
  pinMode(proximity, INPUT);
  pinMode(tap, INPUT);

  Serial.println("Comunicacion serial lista");
}


void loop() {
  // Leen los datos
  int analogTemperature = analogRead(temperature);
  float voltage = (analogTemperature / 1023.0) * 5000;
  float temperatureC = voltage / 100.0;

  int analogPhotoresistor = analogRead(photoresistor);
  int currentState = digitalRead(proximity);
  int tapState = digitalRead(tap);

  // Creamos la forma del paquete para enviarlo 
  String message = "Temp:" + String(temperatureC, 1) +
                   "|Luz:" + String(analogPhotoresistor) +
                   "|Mov:";

  if (currentState == LOW && lastState == HIGH) {
    message += "Detectado";
  } else if (currentState == HIGH && lastState == LOW) {
    message += "Removido";
  } else {
    message += "SinCambio";
  }

  message += "|Toque:" + String(tapState);

  // Enviamos el cifrado
  String cifrado = cifrarBinario(message);
  Serial.println(cifrado);

  lastState = currentState;
  delay(2000);
}

// Cifrado del mensaje en tipo texto
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



