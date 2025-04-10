#include <Arduino.h>
#include <Stepper.h> 
#include <Servo.h>
const int stepsPerRevolution=2000;
const int pasParMinute = 15; // La plage réglable du pas à pas est de 0 à 17
Stepper myStepperH(stepsPerRevolution, 8, 10, 9, 11); // initialisation des pins stepper moteur
Stepper myStepperV(stepsPerRevolution, 1, 4, 3, 5); // initialisation des pins stepper moteur : changer les pins
#define Vpratique 1 // Pas necessaire pour deplacer d'une case à une suivante
int PUSH_BUTTON = 2; //presser le bouton
int Aimant = 11; // ou des sorties pwm
char Dep[] ="B1";
char Arr[] ="C1";
int Choriz;
int Cvert;
int PoseActuel[2];
int echiquier[8][8] = {
  {8, 7, 6, 5, 4, 6, 7, 8},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
}; // LES FONCTIONS
void RetourPinitial(char Arr[]){
  myStepperH.step((-Arr[0]-1-64)*Vpratique);
  myStepperV.step((-Arr[1]-1-'0')*Vpratique);
}
void deplacement(char Dep[2],char Arr[2]){  //placement de l'electro aimant tout en haut à gauche
  myStepperH.step((Dep[0]-65)*Vpratique);
  myStepperV.step((Dep[1]-'0'-1)*Vpratique);//deplacement à la destination de départ
  Cvert=Arr[0]-Dep[0];
  Choriz=Arr[1]-Dep[1];
  digitalWrite(Aimant,HIGH);
  myStepperH.step(int(0.5 * Vpratique));
  delay(200);
  myStepperH.step(Cvert*Vpratique); // valeur ascii de 'A' est 65
  delay(200);
  myStepperV.step(Choriz*Vpratique); // A1 tout à gauche
  delay(200);
  myStepperH.step(int(-0.5 * Vpratique)); 
  digitalWrite(Aimant,LOW);
}//Les étapes dans la fonction deplacement sont calculées en fonction de la différence entre les positions d'origine et d'arrivée.


void setup() {
  pinMode(PUSH_BUTTON,INPUT);
  myStepperH.setSpeed(pasParMinute);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(PUSH_BUTTON) == HIGH){
    deplacement(Dep,Arr);
    RetourPinitial(Arr); //on se trouve a la position d'arrivée pour aller tout en haut à gauche
  }
  delay(1000);
  
}

// echiquier (ou mettre analogread(captX) sur chaque case pour savoir lesquels sont occupés par une pièce mis a part les pieces noires automatisés et celles de la partie blanche initiale: que 32 capteurs )



// RESTE A INTRODUIRE LA PARTIE VERIFICATION DES COUPS