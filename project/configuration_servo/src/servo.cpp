#include <Arduino.h>
#include <Servo.h>

Servo monServo;

void setup() {
  monServo.attach(12); // pin D11 pour le signal
}

void loop() {
  monServo.write(40); //DESACTIVER
  delay(1000);
  monServo.write(100); // ACTIVER
  delay(1000);
}

