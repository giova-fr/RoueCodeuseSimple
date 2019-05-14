# Présentation

Simplifie l'utilisation d'une roue codeuse, la classe est statique, donc une seule roue codeuse peut être utilisée.

#Initialisation et Utilisation

* dans Setup, appeller la méthode Initialise: 
```
#define PIN_CLK 4
#define PIN_DATA 5
#define PIN_BOUTON 0
#define ROUE_NBR_DE_POS 360
#define PULLUP_BT 1

void setup() {
  RoueCodeuseSimple::Initialise(PIN_BOUTON,PULLUP_BT,PIN_CLK,PIN_DATA,ROUE_NBR_DE_POS);
}

* Important :  Dans Loop, ne pas oublier d'appeller la methode _Tick()_

```
**Nombre de pos**
la classe offre la méthode GetPosition, la valeur retournée sera comprise entre 0 et (NRB_DE_POS - 1)

## Evenement
En plus des méthodes d'acces, la librairie offre 2 événements  :

> **void BoutonChanged(bool pos)**
Déclenché lorsque le bouton est enfoncé ou relaché

> **void PositionChanged(int pos, bool sens)**
Déclenclé à chaque cran de rotation de la roue

# Exemple complet
```
#ifdef ARDUINO

#include <Arduino.h>
#include <RoueCodeuseSimple.h>

#define PIN_CLK 4
#define PIN_DATA 5
#define PIN_BOUTON 0
#define ROUE_NBR_DE_POS 4
  #define PULLUP_BT 1
  
//déclaration des callbacks
void QuandBoutonChange(bool position);
void QuandPositionChange(int position, bool sens);

void setup() {
  Serial.begin(9600);
  Serial.println("Bonjour");

  RoueCodeuseSimple::Initialise(PIN_BOUTON,PULLUP_BT,PIN_CLK,PIN_DATA,ROUE_NBR_DE_POS);
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
  if(sens)
    Serial.print("sens     Horraire, position : ");
  else
    Serial.print("sens AntiHorraire, position : ");
  Serial.println(position);
}

#endif
```


## Tests Unitaires

### Requis
* PlatformIO
* gcc (utiliser mingw si windows et ajouter son repertoire bin au PATH global )

### Contenu des tests

Uniquement les tests en natif (arduino non requis) pour les algos. Les entrées sont simulées par des mocks.

### Lancer les tests unitaires :
```
>  pio test -e native --verbose
```
