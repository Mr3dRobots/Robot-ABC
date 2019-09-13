 #include "IRremote.h"
#include "Servo.h"
#undef round

//contrôle moteur
const int sensMotA=12;    //moteur A (droit) Direction (High=sens 1 - Low=sens 2) 
const int vitesseMotA=3;    //moteur A (droit) PWM (Vitesse= 0 -255)
const int sensMotB=13;    //moteur B (gauche) Direction (High=sens 1 - Low=sens 2)
const int vitesseMotB=11;    //moteurr B (gauche) PWM (Vitesse= 0 -255)

//Pin Module récepteur IR et variable
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{

//configurer tous les broches de commande du moteur en sortie
pinMode(sensMotA,OUTPUT);
pinMode(vitesseMotA,OUTPUT);
pinMode(sensMotB,OUTPUT);
pinMode(vitesseMotB,OUTPUT);




Serial.begin(9600);

//le récepteur IR
irrecv.enableIRIn();
}


void loop()
{
Serial.println(results.value, DEC);

//IR signal reçu
if(irrecv.decode(&results))
{

//avant 
if(results.value==3031700205)
{
    digitalWrite(sensMotA, HIGH); //Establishes forward direction of Channel A
  analogWrite(vitesseMotA, 55);    //Spins the motor on Channel B at half speed
    digitalWrite(sensMotB, LOW);   //Disengage the Brake for Channel B
  analogWrite(vitesseMotB, 55);    //Spins the motor on Channel B at half speed
}
//recule
else if(results.value==3031753245)
{
digitalWrite(sensMotA, LOW); //Establishes forward direction of Channel A
  analogWrite(vitesseMotA, 255);    //Spins the motor on Channel B at half speed
   digitalWrite(sensMotB, HIGH); //Establishes forward direction of Channel A
  analogWrite(vitesseMotB, 255);    //Spins the motor on Channel B at half speed
//pivoter vers la gauche (PREVIOUS)
}
else if(results.value==3031718565)
{
digitalWrite(12, LOW); //Establishes forward direction of Channel A
  analogWrite(3, 255);    //Spins the motor on Channel B at half speed
   digitalWrite(13, LOW); //Establishes forward direction of Channel A
  analogWrite(11, 255);    //Spins the motor on Channel B at half speed
  
//pivoter vers la droite (NEXT)
}
else if(results.value==3031734885)
{
digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  analogWrite(3, 255);    //Spins the motor on Channel B at half speed
   digitalWrite(13, HIGH); //Establishes forward direction of Channel A
  analogWrite(11, 255);    //Spins the motor on Channel B at half speed
}
//recevoir la prochaine valeur
irrecv.resume();

//court délai d'attente pour répéter le signal IR
// (empêcher de s'arrêter si aucun signal reçu)
delay(150);
}

else
{
digitalWrite(sensMotA, LOW);    //Spins the motor on Channel B at half speed
digitalWrite(vitesseMotA, LOW);    //Spins the motor on Channel B at half speed
digitalWrite(sensMotB,LOW);    //Spins the motor on Channel B at half speed}}}
digitalWrite(vitesseMotB, LOW);    //Spins the motor on Channel B at half speed
  
}
}

