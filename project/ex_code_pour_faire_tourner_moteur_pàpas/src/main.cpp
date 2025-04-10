// Définition des broches pour contrôler les moteurs pas à pas
#include <Arduino.h>
#define STEP_PIN_X    2   // Broche STEP pour le moteur X (en fonction de votre shield CNC)
#define DIR_PIN_X     5   // Broche DIR pour le moteur X (en fonction de votre shield CNC)
#define ENABLE_PIN_X  8   // Broche ENABLE pour le moteur X (optionnel selon votre shield)

// Paramètres pour le moteur pas à pas
#define STEPS_PER_REV 200 // Nombre de pas pour une révolution complète (à ajuster selon votre moteur)
#define RPM           60  // Vitesse du moteur en tours par minute

void setup() {
  // Initialisation des broches
  delay(100);
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(ENABLE_PIN_X, OUTPUT);
  
  // Désactivation du moteur (ENABLE_PIN_X)
  digitalWrite(ENABLE_PIN_X, LOW);
  
  // Définir la direction du moteur (vers l'avant ou vers l'arrière)
  digitalWrite(DIR_PIN_X, HIGH);  // HIGH pour tourner dans un sens, LOW pour l'autre sens
}

void loop() {
  // Effectuer une révolution complète du moteur
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN_X, HIGH);  // Envoi d'un pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
    digitalWrite(STEP_PIN_X, LOW);   // Fin du pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));  // Attente entre les pas
  }
  
  // Attente après une révolution complète
  delay(1000); // Pause d'une seconde

  // Inverser la direction du moteur pour la prochaine révolution
  digitalWrite(DIR_PIN_X, !digitalRead(DIR_PIN_X));  // Inverser la direction
}

