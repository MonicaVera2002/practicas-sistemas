import serial
import pyrebase

# Configuración de mi proyecto de Firebase
config = {
    "apiKey": "Mi API KEY",
    "authDomain": "MI DOMINIO",
    "databaseURL": "https://practica6-317a4-default-rtdb.firebaseio.com",
    "storageBucket": "practica6-317a4.firebasestorage.app"
}

# Inicia Firebase
firebase = pyrebase.initialize_app(config)
db = firebase.database()

# Comunicación serial con arduino
ser = serial.Serial('/dev/serial0', 9600, timeout=1)

print("Esperando datos...")

while True:
    if ser.in_waiting > 0:
        encrypted_data = ser.readline().decode(errors='ignore').strip()
        print("Los datos se han recibido:", encrypted_data)
        
        # Envío de datos a Firebase
        db.child("datos_cifrados").push({
            "dato": encrypted_data
        })
        
        print("Se han almacenado los datos en Firebase.\n")
