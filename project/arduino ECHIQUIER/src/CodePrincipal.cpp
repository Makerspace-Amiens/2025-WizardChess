#include <Arduino.h>
#include <AccelStepper.h>  // Utilisation de AccelStepper au lieu de Stepper
#include <ctype.h> // pour la fonction isupper
#define STEP_PIN_X    2   // Broche STEP pour le moteur X (en fonction de votre shield CNC)
#define DIR_PIN_X     5   // Broche DIR pour le moteur X (en fonction de votre shield CNC)
#define ENABLE_PIN_X  8   // Broche ENABLE pour le moteur X (optionnel selon votre shield)
#include <Servo.h>

Servo monServo;

#define STEP_PIN_Y 3
#define DIR_PIN_Y 6
#define ENABLE_PIN_Y    9


#define STEPS_PER_REV 200 // Nombre de pas pour une révolution complète (à ajuster selon votre moteur)
#define RPM           60  // Vitesse du moteur en tours par minute
const int Vpratique = 1;              // Facteur de vitesse (utilisé pour ajuster le temps)

int PUSH_BUTTON = 10;  // Bouton pour actionner le déplacement
char Dep[] = "B1";
char Arr[] = "C1";

int Choriz;
int Cvert;
int PoseActuel[2];
char echiquier[8][8] = {
  {'T', 'C', 'F', 'D', 'R', 'F', 'C', 'T'},
  {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
  {'t', 'c', 'f', 'd', 'r', 'f', 'c', 't'}
};


void setup() {
  pinMode(PUSH_BUTTON, INPUT);
  monServo.attach(12); // pin D11 pour le signal
  delay(100);
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(ENABLE_PIN_X, OUTPUT);

  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);
  pinMode(ENABLE_PIN_Y, OUTPUT);


    // Désactivation des moteurs (ENABLE_PIN)
    digitalWrite(ENABLE_PIN_X, LOW);
    digitalWrite(ENABLE_PIN_Y, LOW);
    // Définir la direction du moteur (vers l'avant ou vers l'arrière)
    digitalWrite(DIR_PIN_X, HIGH);  // HIGH pour tourner dans un sens, LOW pour l'autre sens
    digitalWrite(DIR_PIN_Y, HIGH);  // HIGH pour tourner dans un sens, LOW pour l'autre sens
  Serial.begin(9600);
}

void RetourPinitial(char Arr[]) {
  digitalWrite(STEP_PIN_X, HIGH);  // Envoi d'un pas
    delayMicroseconds((60000000*(Arr[0] - 1 - 64) * Vpratique) / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
    digitalWrite(STEP_PIN_X, LOW);   // Fin du pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));  // Attente entre les pas
    digitalWrite(STEP_PIN_Y, HIGH);  // Envoi d'un pas
    delayMicroseconds((60000000*(Arr[1] - '0' - 1) * Vpratique) / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
    digitalWrite(STEP_PIN_Y, LOW);   // Fin du pas
    delayMicroseconds(60000000 / (STEPS_PER_REV * RPM));
}

void deplacement(char Dep[], char Arr[]) {
  Cvert = Arr[0] - Dep[0];
  Choriz = Arr[1] - Dep[1];

//activer l aimantation (axe Z)
  monServo.write(100);
  delay(100);


  // Déplacer en X
  digitalWrite(STEP_PIN_X, HIGH);  // Envoi d'un pas
  delayMicroseconds((60000000*Choriz * Vpratique) / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
  digitalWrite(STEP_PIN_X, LOW);

  delay(100);

  // Déplacer en Y
  digitalWrite(STEP_PIN_Y, HIGH);  // Envoi d'un pas
  delayMicroseconds((Cvert*Vpratique) / (STEPS_PER_REV * RPM));  // Attente pour contrôler la vitesse (en microsecondes)
  digitalWrite(STEP_PIN_Y, LOW);   // Fin du pas

  delay(200);  // Attendre un peu
  delay(1000);
  monServo.write(40); //desactive l'aimantation
}

void loop() {
  delay(100);

  // Effectuer le déplacement de la pièce
  deplacement(Dep, Arr);
  delay(1000);
  // Retour à la position initiale
  RetourPinitial(Arr);

  delay(1000);  // Pause avant le prochain mouvement
}
