#ifdef ARDUINO

#include <Arduino.h>
#include <RoueCodeuseSimple.h>

#define PIN_CLK 4
#define PIN_DATA 5
#define PIN_BOUTON 0
#define ROUE_NBR_DE_POS 4

//déclaration des callbacks
void QuandBoutonChange(bool position);
void QuandPositionChange(int position, bool sens);

void setup() {
  Serial.begin(9600);
  Serial.println("Bonjour");

  RoueCodeuseSimple::Initialise(PIN_BOUTON,PIN_DATA,PIN_CLK,ROUE_NBR_DE_POS);
  RoueCodeuseSimple::AbonneBoutonChanged(QuandBoutonChange); //accroche la callback a l'evenement BoutonChanged
  RoueCodeuseSimple::AbonnePositionChanged(QuandPositionChange); //accroche la callback a l'evenement PositionChange
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

void QuandPositionChange(int position, bool sens)
{
  if(position % 2 == 0)
    return;
  if(sens)
    Serial.print("sens     Horraire, position : ");
  else
    Serial.print("sens AntiHorraire, position : ");
  Serial.println(position);
}

#endif