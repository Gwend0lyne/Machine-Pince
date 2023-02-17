#include <Servo.h>
Servo servo1;
const int pinX = A0;
const int pinY = A1;
const int pinBouton = 34;
#include <Stepper.h>
const int nombrePas = 32*64;
Stepper monMoteur2(nombrePas, 46, 50, 48, 52);
Stepper monMoteur3(nombrePas, 47, 51, 49, 53);
Stepper monMoteur4(nombrePas, 24, 28, 26, 30);
int x = 0;
int y = 0;

 
void setup() {
   pinMode(pinBouton , INPUT_PULLUP);   //on active la résistance pull up 
   Serial.begin(9600);
   monMoteur2.setSpeed(8);
   monMoteur3.setSpeed(8);
   monMoteur4.setSpeed(8);
   servo1.attach(38);
   servo1.write(20);
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

   if (Y<200){
    monMoteur4.step(-100);
    x+=1;
    Serial.println("Y petit");
   }
   if (Y>800){
    monMoteur4.step(100);
    Serial.println("Y grand");
    Serial.println("Boucle 1");
    x-= 1;
   }
   if (X<200){
    monMoteur2.step(-100);
    Serial.println("X petit");
    Serial.println("Boucle 2");
    y+= 1;
   }
   if (X>800){
    monMoteur2.step(100);
    Serial.println("X grand");
    y-=1;
   }
   if(((X<800)&&(X>200))&&((Y<800)&&(Y>200))){
    Serial.println("Boucle 3");
   }
   if (boutonValeur==0){
    monMoteur3.step(1000);
    delay(600);
    //La pince se referme
    servo1.write(120);
    delay(1000);
    monMoteur3.step(-1000);
    monMoteur4.step(x*100);
    monMoteur2.step(y*100);
    //La pince s'ouvre au dessus du trou
    //servo1.write(40); Voir les angles avec Jade
    delay(200);
    servo1.write(20);
    delay(200);
   }

   Serial.print("X:" );
   Serial.print(X);
   Serial.print(" | Y: ");
   Serial.print(Y);
   Serial.print(" | Pulsateur: ");
   Serial.println(boutonValeur);
//   delay(1000);
}
