#include <Arduino.h>

#define STEP_PIN_X    2  // Broche STEP pour le moteur Y (renommée ici X)
#define DIR_PIN_X     5   // Broche DIR pour le moteur Y
#define ENABLE_PIN_X  8   // Broche ENABLE pour le moteur Y

#define STEPS_PER_REV 200 // Nombre de pas par révolution
#define RPM           60  // Vitesse en tours/minute

void setup() {
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(ENABLE_PIN_X, OUTPUT);

  digitalWrite(ENABLE_PIN_X, LOW);      // Activer le moteur (souvent LOW active)
  digitalWrite(DIR_PIN_X, HIGH);        // Sens de rotation
}

void loop() {
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN_X, HIGH);
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));
    digitalWrite(STEP_PIN_X, LOW);
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));
  }

  delay(1000); // Pause d'une seconde
}

/*
 pour la partie Y :
 
// Définition des broches pour contrôler les moteurs pas à pas avec CNC Shield V6
#include <Arduino.h>

#define STEP_PIN_Y    3   // Broche STEP pour le moteur Y (sur CNC Shield V6)
#define DIR_PIN_Y     6   // Broche DIR pour le moteur Y (sur CNC Shield V6)
#define ENABLE_PIN_Y  8   // Broche ENABLE pour le moteur Y (sur CNC Shield V6)

// Paramètres pour le moteur pas à pas
#define STEPS_PER_REV 200 // Nombre de pas pour une révolution complète (à ajuster selon votre moteur)
#define RPM           60  // Vitesse du moteur en tours par minute

void setup() {
  // Initialisation des broches
  delay(100);
  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);
  pinMode(ENABLE_PIN_Y, OUTPUT);
  
  // Désactivation du moteur (ENABLE_PIN_Y)
  digitalWrite(ENABLE_PIN_Y, LOW);  // ENABLE_PIN_Y doit être LOW pour activer le moteur
  
  // Définir la direction du moteur (vers l'avant ou vers l'arrière)
  digitalWrite(DIR_PIN_Y, HIGH);  // HIGH pour tourner dans un sens, LOW pour l'autre sens
}

void loop() {
  // Effectuer une révolution complète du moteur
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN_Y, HIGH);  // Envoi d'un pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
    digitalWrite(STEP_PIN_Y, LOW);   // Fin du pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));  // Attente entre les pas
  }
  
  // Attente après une révolution complète
  delay(1000); // Pause d'une seconde

  // Inverser la direction du moteur pour la prochaine révolution
  digitalWrite(DIR_PIN_Y, !digitalRead(DIR_PIN_Y));  // Inverser la direction
}

*/
 
 