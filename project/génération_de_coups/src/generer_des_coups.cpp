#include <Arduino.h>
#include <ctype.h> // pour la fonction isupper



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
  Serial.begin(9600);
  randomSeed(analogRead(A0)); // meilleur que srand(time(0)) sur Arduino
}

void loop() {
  int x = rand() % 8;
  int y = rand() % 8;

  Serial.print("Case aléatoire : ");
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);

  delay(1000);
}