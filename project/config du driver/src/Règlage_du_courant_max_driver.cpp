#include <Arduino.h>


int driver = 8; //(driver enable sur pin 8)

void setup() {
  pinMode(driver,OUTPUT);
  digitalWrite(driver,LOW);
}

void loop() {
  
}
