#include <Arduino.h>

const int ledPin = 13; // Broche à laquelle la LED est connectée

void setup() {
    // Initialisation de la communication série et de la LED
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT); // Définir la broche de la LED comme sortie
}

void loop() {
    // Vérifier si des données sont disponibles sur le port série
    if (Serial.available() > 0) {
        String command = Serial.readString(); // Lire la chaîne reçue
        command.trim(); // Supprimer les espaces inutiles

        // Vérifier les commandes reçues et allumer/éteindre la LED
        if (command == "ON") {
            digitalWrite(ledPin, HIGH); // Allumer la LED
            Serial.println("LED allumée");
        }
        else if (command == "OFF") {
            digitalWrite(ledPin, LOW); // Éteindre la LED
            Serial.println("LED éteinte");
        }
        else {
            Serial.println("Commande invalide");
        }
    }
}

