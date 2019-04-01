//MAIN
#include "sensor_battery_liquid.h"
#include "sensor_rgb.h"
#include "sensor_spray.h"
#include "sensor_ultrasonic.h"
#include "path_correction.h"
#define L_IN_Positive 8   
#define L_IN_Negative 9    
#define R_IN_Positive 10    
#define R_IN_Negative 7    
#define L_EN 3           
#define R_EN 5
#define PotentiometerPin 0
// Raphael pin
const int relayPin = 8;

float ultrasonic_measure;
bool weed_presence = 0;
bool breakk = false; // cette variable permet au système de spray du desherbant de temporiser
int i = 0;
/*float Batterie;                      //Variable du niveau de batterie (%) #Adeline
bool Desherbant;                     //Variable du niveau de désherbant #Adeline
bool Herbe;                          //Variable de la détection de mavaises herbes #Olivier*/
 

void setup() {
  Serial.begin(9600);
  pinMode(L_IN_Positive,OUTPUT);
  pinMode(L_IN_Negative,OUTPUT);
  pinMode(R_IN_Positive,OUTPUT);
  pinMode(R_IN_Negative,OUTPUT);
  pinMode(L_EN,OUTPUT); 
  pinMode(R_EN,OUTPUT);
  //pinMode(PotentiometerPin, INPUT);

  digitalWrite(L_IN_Positive,1);
  digitalWrite(L_IN_Negative,0);
  digitalWrite(R_IN_Positive,1);
  digitalWrite(R_IN_Negative,0);
  analogWrite(L_EN,0);
  analogWrite(R_EN,0);

  setup_rgb();
  setup_battery_liquid();
  setup_spray(relayPin);
  }

void pathCorrection() {
  
}



void loop() {
  
  ultrasonic_measure = srf08_mesure(ultrasonic_measure);
  Serial.println(ultrasonic_measure);

  if (breakk) {
    i++;
    if (i>=43) {
      breakk=false;
      i=0;
      digitalWrite(relayPin, LOW);
    }
  } else {
    breakk = spray(relayPin, 100, 100, weed_presence, breakk); // les valeurs de niveau de batterie et de desherbant ont été mises a 100 pour des raisons de test
  }
  
  weed_presence = get_rgb(weed_presence);
  Serial.println(weed_presence);
  

  
  loop_battery_liquid();
}

