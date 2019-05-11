#include <Arduino.h>
#include <RoueCodeuseSimple.h>
int PinCLK=4;
int PinDT=5;
int PinSW=0;
int NbrDePositions = 4;

#define BUF_LEN 128 
char buffer[BUF_LEN];

void setup() {
  Serial.begin(9600);
  Serial.println("Bonjour");
  RoueCodeuseSimple::Initialise(PinSW,PinDT,PinSW,NbrDePositions);
  Serial.println("roue codeuse configurée");
  
  Serial.print("etat bouton : ");
  Serial.println(RoueCodeuseSimple::GetBoutonStatut());
  Serial.print("position roue : ");
  Serial.println(RoueCodeuseSimple::GetPosition());
}

void loop() {
  RoueCodeuseSimple::Tick();
}
