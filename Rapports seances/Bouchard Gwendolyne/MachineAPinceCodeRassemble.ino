#include <Servo.h>
Servo servo1;
const int pinX = A0;
const int pinY = A1;
const int pinBouton = 23;
#include <Stepper.h>
const int nombrePas = 32*64;
Stepper monMoteur(nombrePas, 24, 25, 26, 27);
Stepper monMoteur2(nombrePas, 46, 50, 48, 52);
Stepper monMoteur3(nombrePas, 47, 51, 49, 53);
int x = 0;
int y = 0;

 
void setup() {
   pinMode(pinBouton , INPUT_PULLUP);   //on active la résistance pull up 
   Serial.begin(9600);
   monMoteur.setSpeed(5);
   monMoteur2.setSpeed(5);
   monMoteur3.setSpeed(5);
   servo1.attach(38); //bizarre mais j'y mit comme Jade
   servo1.attach(38, 544, 2400);
   servo1.detach(); //c'est biazzare un peu?
}
 
void loop() {
   int X = 0;
   int Y = 0;
   bool boutonValeur = false;
 
   //on lit les valeurs
   X = analogRead(pinX);
   /*il est nécessaire de faire un pause entre les lectures des différents
   pins analogiques  si on veut éviter l'obtention double de la même
   lecture (dû au fonctionnement interne des pins) */
   delay(10);
   Y = analogRead(pinY);
   boutonValeur = digitalRead(pinBouton);

   if (X<200){
    monMoteur.step(100);
    x+=1;
   }
   if (X>800){
    monMoteur.step(-100);
    x-= 1;
   }
   if (Y<200){
    monMoteur2.step(100);
    y+= 1;
   }
   if (Y>800){
    monMoteur2.step(-100);
    y-=1;
   }
   if (boutonValeur==0){
    monMoteur3.step(1000);
    delay(1000);
    //La pince se referme
    //servo1.write(150); Voir les angles avec Jade
    servo1.write(90);
    monMoteur3.step(-1000);
    monMoteur.step(-1*x*100);
    monMoteur2.step(-1*y*100);
    //La pince s'ouvre au dessus du trou
    //servo1.write(40); Voir les angles avec Jade
    Servo1.writeMicroseconds(90);
   }

   Serial.print("X:" );
   Serial.print(X);
   Serial.print(" | Y: ");
   Serial.print(Y);
   Serial.print(" | Pulsateur: ");
   Serial.println(boutonValeur);
//   delay(1000);
}
