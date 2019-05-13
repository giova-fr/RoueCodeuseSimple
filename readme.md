#Présentation
Simplifie l'utilisation d'une roue codeuse, la classe est statique, donc une seule roue codeuse peut être utilisée.

#Initialisation et Utilisation
* dans Setup, appeller la méthode Initialise: 
```
#define PIN_CLK 4
#define PIN_DATA 5
#define PIN_BOUTON 0
#define ROUE_NBR_DE_POS 360

void setup() {
  RoueCodeuseSimple::Initialise(PIN_CLK,PIN_DATA,PIN_BOUTON,ROUE_NBR_DE_POS);
}

* Important :  Dans Loop, ne pas oublier d'appeller la methode _Tick()_

```
**Nombre de pos**
la classe offre la méthode GetPosition, la valeur retournée sera comprise entre 0 et (NRB_DE_POS - 1)

##Evenement
En plus des méthodes d'acces, la librairie offre 2 événements  :

###void BoutonChanged(bool pos)
Déclenché lorsque le bouton est enfoncé ou relaché

###void PositionChanged(int pos, bool sens)
Déclenclé à chaque cran de rotation de la roue

#Exemple complet



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
