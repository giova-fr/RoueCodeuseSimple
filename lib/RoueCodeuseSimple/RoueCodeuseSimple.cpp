#include "RoueCodeuseSimple.h"
#ifndef UNIT_TEST
    #include <Arduino.h>
#endif


int RoueCodeuseSimple::_brocheBouton = 0;
int RoueCodeuseSimple::_brocheData = 0;
int RoueCodeuseSimple::_brocheClock = 0;
short RoueCodeuseSimple::_position = 0;
short RoueCodeuseSimple::_positionMax = 0;
bool RoueCodeuseSimple::_boutonStatut = true;
int RoueCodeuseSimple::_dataAvant = 0;

void   RoueCodeuseSimple::Initialise(int pinBouton, int pinData, int pinClock,short positionMax)
{
    if(!IsReady())
    {
#ifndef UNIT_TEST
        pinMode(pinClock,INPUT);
        pinMode(pinData,INPUT);
        pinMode(pinBouton,INPUT);
#endif
        _brocheClock = pinClock;
        _brocheData = pinData;
        _brocheBouton = pinBouton;
        _positionMax = positionMax-1;
    };
};

bool  RoueCodeuseSimple::IsReady(){
    return !(_brocheClock == 0 && _brocheData == 0 && _brocheBouton == 0);
}

short  RoueCodeuseSimple::GetPosition(){
    return RoueCodeuseSimple::_position;
};

bool  RoueCodeuseSimple::GetBoutonStatut(){
    return RoueCodeuseSimple::_boutonStatut;
};

void RoueCodeuseSimple::Tick(){

}