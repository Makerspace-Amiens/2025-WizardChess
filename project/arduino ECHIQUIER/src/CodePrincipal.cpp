#include <Arduino.h>
#include <AccelStepper.h>  // Utilisation de AccelStepper au lieu de Stepper
#include <ctype.h> // pour la fonction isupper

const int stepsPerRevolution = 2000;  // Nombre de pas par révolution pour votre moteur
const int pasParMinute = 15;          // Vitesse du moteur (ajustable)
const int Vpratique = 1;              // Facteur de vitesse (utilisé pour ajuster le temps)

int PUSH_BUTTON = 10;  // Bouton pour actionner le déplacement
int Aimant = 11;       // Sortie pour l'électro-aimant

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
  {'t', 'c', 'f', 'd', 'r', 'f', 'c', 'r'}
};

// Définir les pins pour les moteurs (basé sur CNC Shield)
const int stepPinX = 2;  // X Step
const int dirPinX = 5;   // X Direction
const int stepPinY = 3;  // Y Step
const int dirPinY = 4;   // Y Direction

AccelStepper myStepperX(AccelStepper::DRIVER, stepPinX, dirPinX);  // Initialiser pour X
AccelStepper myStepperY(AccelStepper::DRIVER, stepPinY, dirPinY);  // Initialiser pour Y

void setup() {
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(Aimant, OUTPUT);
  
  // Configuration de la vitesse et de l'accélération des moteurs
  myStepperX.setMaxSpeed(1000);  // Définir la vitesse maximale du moteur X
  myStepperX.setAcceleration(500);  // Définir l'accélération du moteur X
  
  myStepperY.setMaxSpeed(1000);  // Définir la vitesse maximale du moteur Y
  myStepperY.setAcceleration(500);  // Définir l'accélération du moteur Y
  
  Serial.begin(9600);
}

void RetourPinitial(char Arr[]) {
  myStepperY.moveTo((Arr[0] - 1 - 64) * Vpratique);
  myStepperY.runToPosition();
  myStepperX.moveTo((Arr[1] - '0' - 1) * Vpratique);
  myStepperX.runToPosition();
}

void deplacement(char Dep[], char Arr[]) {
  int Cvert = Arr[0] - Dep[0];
  int Choriz = Arr[1] - Dep[1];

  digitalWrite(Aimant, HIGH);  // Activer l'électro-aimant

  // Déplacer en X
  myStepperX.moveTo(Choriz * Vpratique);
  while (myStepperX.isRunning()) {
    myStepperX.run();
  }

  // Déplacer en Y
  myStepperY.moveTo(Cvert * Vpratique);
  while (myStepperY.isRunning()) {
    myStepperY.run();
  }

  delay(200);  // Attendre un peu
  digitalWrite(Aimant, LOW);  // Désactiver l'électro-aimant
}

void loop() {
  delay(100);

  // Effectuer le déplacement de la pièce
  deplacement(Dep, Arr);

  // Retour à la position initiale
  RetourPinitial(Arr);

  delay(1000);  // Pause avant le prochain mouvement
}
