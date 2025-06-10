#include <Arduino.h>
#include <Servo.h>

#define STEP_PIN_X    3
#define DIR_PIN_X     6
#define ENABLE_PIN_X  9

#define STEP_PIN_Y    2
#define DIR_PIN_Y     5
#define ENABLE_PIN_Y  8

bool dirX, dirY;
#define STEPS_PER_REV 200
#define RPM           60

Servo monServo;

const int PAS_PAR_CASE = 250;
int i = 0;

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

  digitalWrite(DIR_PIN_X, HIGH);
  digitalWrite(DIR_PIN_Y, HIGH);

  Serial.begin(9600);
  delay(100);
}

void stepMotor(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction ? HIGH : LOW);
  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
    digitalWrite(stepPin, LOW);
    delayMicroseconds(60000000L / (STEPS_PER_REV * RPM));
  }
}

void retourAOrigine(char* positionActuelle) {
  monServo.write(40); // désactive l'aimant

  int xDelta = positionActuelle[0] - 'B'; // origine colonne B
  int yDelta = positionActuelle[1] - '2'; // origine ligne 2

  bool retourX = (xDelta > 0); // si on est à droite, revenir à gauche
  bool retourY = (yDelta < 0); // si on est plus haut, revenir en bas

  int xSteps = abs(xDelta) * PAS_PAR_CASE;
  int ySteps = abs(yDelta) * PAS_PAR_CASE;

  stepMotor(STEP_PIN_X, DIR_PIN_X, xSteps, retourX);
  stepMotor(STEP_PIN_Y, DIR_PIN_Y, ySteps, retourY);
}

void deplacement(char* dep, char* arr) {
  int xDelta = arr[0] - dep[0];
  int yDelta = arr[1] - dep[1];

  dirX = (xDelta < 0);
  dirY = (yDelta > 0);

  int xSteps = abs(xDelta) * PAS_PAR_CASE;
  int ySteps = abs(yDelta) * PAS_PAR_CASE;

  stepMotor(STEP_PIN_Y, DIR_PIN_Y, ySteps, dirY);
  stepMotor(STEP_PIN_X, DIR_PIN_X, xSteps, dirX);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    received.trim();
    delay(100);
    Serial.println(received);
    i++;

    if (received.length() == 4) {
      char dep[3] = {received.charAt(0), received.charAt(1), '\0'};
      char arr[3] = {received.charAt(2), received.charAt(3), '\0'};
      char origin[3] = {'B', '2', '\0'};  // position de repos

      deplacement(origin, dep);

      if (i < 16 && received[0] == received[3]) {
        monServo.write(100); // active l'aimant
        deplacement(dep, arr);
        retourAOrigine(arr);
      } else {
        int demiCase = PAS_PAR_CASE / 2;
        monServo.write(100);
        stepMotor(STEP_PIN_X, DIR_PIN_X, demiCase, true);  // avance d'une demi-case
        deplacement(dep, arr);
        stepMotor(STEP_PIN_X, DIR_PIN_X, demiCase, false); // recule d'une demi-case
        retourAOrigine(arr);
      }
    }

    else if (received.length() == 6) {
      char dep[3] = {received.charAt(0), received.charAt(1), '\0'};
      char inter[3] = {received.charAt(2), received.charAt(3), '\0'};
      char arr[3] = {received.charAt(4), received.charAt(5), '\0'};
      char origin[3] = {'B', '2', '\0'};

      deplacement(origin, dep);
      monServo.write(100);
      deplacement(dep, inter);
      deplacement(inter, arr);
      retourAOrigine(arr);
    }
  }
}
