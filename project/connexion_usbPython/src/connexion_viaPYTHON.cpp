#include <Arduino.h>
#include <Servo.h>

Servo monServo;
void setup() {
  monServo.attach(12);
  monServo.write(0);
  Serial.begin(9600);
  delay(100);}

void loop() {
  monServo.write(0);
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n'); // Lis jusqu'au saut de ligne
    Serial.print("Reçu : ");
    Serial.println(received); // Affiche ce qui a été reçu
    if (received[2]== 'D'){
      monServo.write(180);
      delay(500);

    }
  }
}

