#programme test envoie message vers arduino
import serial
import time

arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)
time.sleep(2)  # Attendre que l'Arduino soit prêt

def envoyer_message(message):
    print(f"Envoi : {message}")
    arduino.write((message + '\n').encode())  # Encoder et ajouter \n
    time.sleep(0.5)  # Attendre que l'Arduino réponde

    # Lire la réponse
    while arduino.in_waiting:
        reponse = arduino.readline().decode().strip()
        print(f"Arduino a répondu : {reponse}")

# Exemple : envoi de messages
envoyer_message("Bonjour Arduino")
envoyer_message("Test de message")

arduino.close()