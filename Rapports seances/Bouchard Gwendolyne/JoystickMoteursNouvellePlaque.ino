const int pinX = A0;
const int pinY = A1;
const int pinBouton = 23;
#include <Stepper.h>
const int nombrePas = 32*64;
Stepper monMoteur(nombrePas, 24, 25, 26, 27);
Stepper monMoteur2(nombrePas, 46, 50, 48, 52);
Stepper monMoteur3(nombrePas, 47, 51, 49, 53);
 
void setup() {
   pinMode(pinBouton , INPUT_PULLUP);   //on active la résistance pull up 
   Serial.begin(9600);
   monMoteur.setSpeed(5);
   monMoteur2.setSpeed(5);
   monMoteur3.setSpeed(5);
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
   }
   if (X>800){
    monMoteur.step(-100);
   }
   if (Y<200){
    monMoteur2.step(100);
   }
   if (Y>800){
    monMoteur2.step(-100);
   }
   if (boutonValeur==0){
    monMoteur3.step(2000);
   }

   Serial.print("X:" );
   Serial.print(X);
   Serial.print(" | Y: ");
   Serial.print(Y);
   Serial.print(" | Pulsateur: ");
   Serial.println(boutonValeur);
//   delay(1000);
}
