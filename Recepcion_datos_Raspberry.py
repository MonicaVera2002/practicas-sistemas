import serial

XOR_KEY = 0x5A  # igual que Arduino

ser = serial.Serial("/dev/ttyUSB0", 9600)

while True:
    encrypted = ser.readline().rstrip(b"\n")
    decrypted = bytes([b ^ XOR_KEY for b in encrypted])
    print("Decrypted:", decrypted.decode())
