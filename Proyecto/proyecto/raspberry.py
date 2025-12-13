import serial
import json
import requests
import time

arduino = serial.Serial('/dev/serial0', 9600, timeout=1)
time.sleep(2)

CLAVE_XOR = 0x5A
FIREBASE_URL = "https://visionarios-4015a-default-rtdb.firebaseio.com/"

def bin_fix(b):
    return b.zfill(8)

def xor_decrypt(value):
    return value ^ CLAVE_XOR

# Descifrar texto normal
def descifrar_mensaje_bin(bin_line):
    partes = bin_line.split()
    texto = ""
    for b in partes:
        try:
            val = int(b, 2)
            texto += chr(xor_decrypt(val))
        except:
            texto += "?"
    return texto

def descifrar_float_bin(bin_line):
    txt = descifrar_mensaje_bin(bin_line)
    try:
        return float(txt)
    except:
        return None

def descifrar_entero_bin(bin_line):
    val_cif = int(bin_line, 2)
    return xor_decrypt(val_cif)

def proc_paq(paquete):

    if len(paquete) != 10:
        print("Paquete incompleto:", len(paquete))
        return None

    # Valores
    temp = descifrar_float_bin(paquete[0])
    mq2 = descifrar_entero_bin(paquete[1])
    sound = descifrar_entero_bin(paquete[2])
    sw = descifrar_entero_bin(paquete[3])
    pir = descifrar_entero_bin(paquete[4])

    # Mensajes
    msg_temp = descifrar_mensaje_bin(paquete[5])
    msg_mq2 = descifrar_mensaje_bin(paquete[6])
    msg_ky = descifrar_mensaje_bin(paquete[7])
    msg_sw = descifrar_mensaje_bin(paquete[8])
    msg_pir = descifrar_mensaje_bin(paquete[9])

    return {
        "temperatura": temp,
        "mq2": mq2,
        "sound": sound,
        "sw420": sw,
        "pir": pir,
        "msg_temp": msg_temp,
        "msg_mq2": msg_mq2,
        "msg_ky": msg_ky,
        "msg_sw": msg_sw,
        "msg_pir": msg_pir
    }

buffer = []
capturando = False
lineas_esperadas = 10

while True:
    try:
        line = arduino.readline().decode(errors="ignore").strip()
        if not line:
            continue

        print("Serial:", line)

        if line == "CONTROL":
            buffer = []
            capturando = True
            continue

        if capturando:
            buffer.append(line)

            if len(buffer) == lineas_esperadas:

                data = proc_paq(buffer)
                if data:

                    requests.post(FIREBASE_URL + "lm35.json",
                        json={"valor": data["temperatura"]})
                    requests.post(FIREBASE_URL + "mq2.json",
                        json={"valor": data["mq2"]})
                    requests.post(FIREBASE_URL + "ruido.json",
                        json={"valor": data["sound"]})
                    requests.post(FIREBASE_URL + "vibracion.json",
                        json={"valor": data["sw420"]})
                    requests.post(FIREBASE_URL + "pir.json",
                        json={"valor": data["pir"]})

                    print("===== DECIFRADO =====")
                    print(json.dumps(data, indent=4, ensure_ascii=False))
                    print("=========================")

                capturando = False
                buffer = []

    except Exception as e:
        print("Error:", e)

    time.sleep(0.1)






