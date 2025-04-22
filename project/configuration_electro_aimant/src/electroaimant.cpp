#include <Arduino.h>
int spindlePin = 4;  // Pin de sortie Spindle sur le CNC Shield (peut être 4 ou 5 selon ton modèle)

void setup() {
  pinMode(spindlePin, OUTPUT);  // Définit la pin comme une sortie
}

void loop() {
  digitalWrite(spindlePin, HIGH);  // Active l'électroaimant (met la broche à HIGH)
  delay(1000);  // L'électroaimant reste activé pendant 1 seconde
  digitalWrite(spindlePin, LOW);   // Désactive l'électroaimant (met la broche à LOW)
  delay(1000);  // L'électroaimant reste désactivé pendant 1 seconde
}
