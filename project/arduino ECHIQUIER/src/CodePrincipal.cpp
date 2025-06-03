#include <Arduino.h>
#include <Servo.h>

#define STEP_PIN_X    2
#define DIR_PIN_X     5
#define ENABLE_PIN_X  8

#define STEP_PIN_Y    3
#define DIR_PIN_Y     6
#define ENABLE_PIN_Y  9

#define STEPS_PER_REV 200
#define RPM           60

Servo monServo;

void setup() {
  monServo.attach(12);
  monServo.write(40); // désactive l'aimantation

  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(ENABLE_PIN_X, OUTPUT);

  pinMode(STEP_PIN_Y, OUTPUT);
  pinMode(DIR_PIN_Y, OUTPUT);
  pinMode(ENABLE_PIN_Y, OUTPUT);


  digitalWrite(ENABLE_PIN_X, LOW);
  digitalWrite(ENABLE_PIN_Y, LOW);

  digitalWrite(DIR_PIN_X, HIGH);  // HIGH pour tourner dans un sens, LOW pour l'autre sens
  digitalWrite(DIR_PIN_Y, HIGH); 

  Serial.begin(9600);
  delay(100);
}

// Fonction qui fait un certain nombre de pas sur un moteur donné dans une direction donnée
void stepMotor(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction ? HIGH : LOW);
  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
    digitalWrite(stepPin, LOW);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
  }
}

// Fonction qui fait un seul pas, utile pour déplacement pas à pas
void stepMotorStep(int stepPin, int dirPin, bool direction) {
  digitalWrite(dirPin, direction ? HIGH : LOW);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
  digitalWrite(stepPin, LOW);
  delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
}

// Retour à la position d'origine (A1) depuis la position donnée
void RetourPinitial(char* position) {
  monServo.write(40); // désactive l'aimantation

  int xSteps = position[0] - 'A'; // calcul du nombre de pas X vers origine
  int ySteps = position[1] - '1'; // calcul du nombre de pas Y vers origine

  // Retour vers origine, toujours dans la direction "false" (vers origine)
  stepMotor(STEP_PIN_X, DIR_PIN_X, xSteps, false);
  stepMotor(STEP_PIN_Y, DIR_PIN_Y, ySteps, false);
}

void deplacement(char* dep, char* arr) {
  const int PAS_PAR_CASE = 50;  // À ajuster selon ton moteur et ton échiquier

  int xDelta = arr[0] - dep[0];  // 'E' - 'B' = +3 colonnes
  int yDelta = arr[1] - dep[1];  // '4' - '2' = +2 rangées

  bool xDir = (xDelta > 0);
  bool yDir = (yDelta > 0);

  int xSteps = abs(xDelta) * PAS_PAR_CASE;
  int ySteps = abs(yDelta) * PAS_PAR_CASE;

  monServo.write(100); // activation aimant
  delay(300);

  // D'abord Y
  stepMotor(STEP_PIN_Y, DIR_PIN_Y, ySteps, yDir);

  // Puis X
  stepMotor(STEP_PIN_X, DIR_PIN_X, xSteps, xDir);

  delay(300);
  monServo.write(40);  // désactivation aimant
  delay(200);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    received.trim(); // nettoie la commande reçue
    delay(100);
    Serial.println(received); // répond IMMÉDIATEMENT

    // Puis traitement logique
    if (received.length() == 4) {
      char dep[3] = {received.charAt(0), received.charAt(1), '\0'};
      char arr[3] = {received.charAt(2), received.charAt(3), '\0'};

      int demiCase = STEPS_PER_REV / 2;
      stepMotor(STEP_PIN_X, DIR_PIN_X, demiCase, true);
      deplacement(dep, arr);
      stepMotor(STEP_PIN_X, DIR_PIN_X, demiCase, false);

      RetourPinitial(arr);
    }

    else if (received.length() == 6) {
      char dep[3] = {received.charAt(0), received.charAt(1), '\0'};
      char inter[3] = {received.charAt(2), received.charAt(3), '\0'};
      char arr[3] = {received.charAt(4), received.charAt(5), '\0'};

      deplacement(dep, inter);
      deplacement(inter, arr);
      RetourPinitial(arr);
      Serial.println("DONE");
    }
  }
}



