#ifdef ARDUINO

#include <Arduino.h>
#include <RoueCodeuseSimple.h>

#define PIN_CLK 4
#define PIN_DATA 5
#define PIN_BOUTON 0
#define ROUE_MAXPOS 4

//déclaration des callbacks
void QuandBoutonChange(bool position);

#define BUF_LEN 128 
char buffer[BUF_LEN];

void setup() {
  Serial.begin(9600);
  Serial.println("Bonjour");

  RoueCodeuseSimple::Initialise(PIN_CLK,PIN_DATA,PIN_BOUTON,ROUE_MAXPOS);
  RoueCodeuseSimple::AbonneBoutonChanged(QuandBoutonChange); //accroche la callback a l'evenement BoutonChanged
  Serial.println("roue codeuse configurée");
  
  Serial.print("etat bouton initial: ");
  Serial.println(RoueCodeuseSimple::GetBoutonStatut());
  Serial.print("position roue  initial: ");
  Serial.println(RoueCodeuseSimple::GetPosition());
}

void loop() {
  RoueCodeuseSimple::Tick(); //Et c'est tout, voir les methodes de callback ci dessous
}

void QuandBoutonChange(bool position)
{
  if(position)
    Serial.println("--- bouton relaché ---");
  else
    Serial.println("---bouton enfoncé---");
  
}

#endif