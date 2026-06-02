import serial

# Se ajusta el puerto serial utilizado para esta práctica
ser = serial.Serial('/dev/ttyUSB0', 9600)

#Se manda un mensaje que la Raspberry esta recibiendo los datos
print("Raspberry lista recibiendo datos cifrados...\n")

#Se comprueba que se esta recibiendo los datos y se manda solo el mensaje
while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        print("Cifrado recibido:", data)
