#include <Arduino.h>
void setup() {
  Serial.begin(9600); // Démarre la communication série à 9600 bauds
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n'); // Lis jusqu'au saut de ligne
    Serial.print("Reçu : ");
    Serial.println(received); // Affiche ce qui a été reçu
  }
}

