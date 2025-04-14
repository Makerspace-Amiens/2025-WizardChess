#include <Arduino.h>
#include <ctype.h> // pour la fonction isupper

int x;
int y;
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
  do{
  int x = rand() % 8;
  int y = rand() % 8;

  Serial.print("Case aléatoire : ");
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);}while(echiquier[x][y]==0);

  delay(1000);
}