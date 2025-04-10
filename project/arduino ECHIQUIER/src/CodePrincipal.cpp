#include <Arduino.h>
#include <ctype.h> // pour la fonction isupper
const int stepsPerRevolution=2000;
const int pasParMinute = 15; // La plage réglable du pas à pas est de 0 à 17
const int stepPin1 = 2;
const int dirPin1 = 3; //steper H
const int stepPin2 = 4;
const int dirPin2 = 5;
#define Vpratique 1 // Pas necessaire pour deplacer d'une case à une suivante
int PUSH_BUTTON = 10; //presser le bouton
int Aimant = 11; // ou des sorties pwm
char Dep[] ="B1";
char Arr[] ="C1";
int Choriz;
int Cvert;
int PoseActuel[2];
char echiquier[8][8] = {
  {'T','C','F','D','R','F','C','T'},
  {'P','P','P','P','P','P','P','P'},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {'p','p','p','p','p','p','p','p'},
  {'t','c','f','d','r','f','c','r'}
};      /* verifier si le caractere est une majuscule: if(isupper(char)){
  printf("le charest une majuscule")}
 verifier si le caractere est une minuscule:  if

*/
void setup() {
  pinMode(PUSH_BUTTON,INPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(PUSH_BUTTON==1){
    void deplacement(char Dep[2],char Arr[2]);
    void RetourPinitial(char Arr[]); //on se trouve a la position d'arrivée pour aller tout en haut à gauche
  }
  delay(1000);
  
}

// echiquier (ou mettre analogread(captX) sur chaque case pour savoir lesquels sont occupés par une pièce mis a part les pieces noires automatisés et celles de la partie blanche initiale: que 32 capteurs )


void RetourPinitial(char Arr[]){
  digitalWrite(dirPin1, HIGH); // Active la rotation dans le sens horaire
  delayMicroseconds((-Arr[0]-1-64)*Vpratique);
  myStepperV.step((-Arr[1]-1-'0')*Vpratique);
}
void deplacement(char Dep[2],char Arr[2]){  //placement de l'electro aimant tout en haut à gauche
  digitalWrite(dirPin1, HIGH);
  delayMicroseconds((Dep[0]-65)*Vpratique);
  //il faut arreter le moteur
  digitalWrite(dirPin2, HIGH);
  delayMicroseconds((Dep[1]-'0'-1)*Vpratique);//deplacement à la destination de départ
  Cvert=Arr[0]-Dep[0];
  Choriz=Arr[1]-Dep[1];
  digitalWrite(Aimant,HIGH);
  myStepperH.step(0.5*Vpratique);
  delay(200);
  myStepperH.step(Cvert*Vpratique); // valeur ascii de 'A' est 65
  delay(200);
  myStepperV.step(Choriz*Vpratique); // A1 tout à gauche
  delay(200);
  digitalWrite(dirPin1, LOW);
  delayMicroseconds(0.5*Vpratique);
  digitalWrite(Aimant,LOW);
}

// RESTE A INTRODUIRE LA PARTIE VERIFICATION DES COUPS