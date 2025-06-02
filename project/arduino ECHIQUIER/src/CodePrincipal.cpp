#include <Arduino.h>
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
const int Vpratique = 1;

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

  Serial.begin(9600);
}

// Fonction pour déplacer un moteur un certain nombre de pas
void stepMotor(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction ? HIGH : LOW);
  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
    digitalWrite(stepPin, LOW);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
  }
}

// Retour à la position initiale
void RetourPinitial(char* position) {
  monServo.write(40); // désactive l'aimantation

  int xSteps = (position[0] - 'A');  // 'A' à 'H'
  int ySteps = (position[1] - '1');  // '1' à '8'

  stepMotor(STEP_PIN_X, DIR_PIN_X, xSteps, false); // Retour X
  stepMotor(STEP_PIN_Y, DIR_PIN_Y, ySteps, false); // Retour Y
}

// Déplacement entre deux positions (ex: "A2" -> "B3")
void deplacement(char* dep, char* arr) {
  int xDelta = arr[0] - dep[0];  // colonne
  int yDelta = arr[1] - dep[1];  // ligne

  monServo.write(100); // active l'aimantation
  delay(100);

  stepMotor(STEP_PIN_X, DIR_PIN_X, xDelta, xDelta > 0);
  delay(100);
  stepMotor(STEP_PIN_Y, DIR_PIN_Y, yDelta, yDelta > 0);

  delay(1000);
  monServo.write(40); // désactive l'aimantation
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    delay(100);

    if (received.length() >= 4) {
      char dep[3] = {received.charAt(0), received.charAt(1), '\0'};
      char arr[3] = {received.charAt(2), received.charAt(3), '\0'};

      deplacement(dep, arr);
      delay(1000);
      RetourPinitial(arr);
      delay(1000);
    }
  }
}
//adapter les HIGH et LOW et Vpratique