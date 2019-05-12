#include "RoueCodeuseSimple.h"
#ifdef ARDUINO
    #include <Arduino.h>
#endif


int RoueCodeuseSimple::_brocheBouton = 0;
int RoueCodeuseSimple::_brocheData = 0;
int RoueCodeuseSimple::_brocheClock = 0;
short RoueCodeuseSimple::_position = 0;
short RoueCodeuseSimple::_positionMax = 0;
bool RoueCodeuseSimple::_boutonStatut = true;
bool RoueCodeuseSimple::_boutonAvant = true;
int RoueCodeuseSimple::_dataAvant = 0;
ptFnReadDigital RoueCodeuseSimple::__ReadDigital = 0;

ptFnBoutonStatus RoueCodeuseSimple::_boutonPressedCallback = 0;

void   RoueCodeuseSimple::Initialise(int pinBouton, int pinData, int pinClock,short positionMax)
{
    if(!IsReady())
    {
#ifdef ARDUINO
        pinMode(pinClock,INPUT);
        pinMode(pinData,INPUT);
        pinMode(pinBouton,INPUT);
        __ReadDigital = digitalRead;
#endif
        _brocheClock = pinClock;
        _brocheData = pinData;
        _brocheBouton = pinBouton;
        _positionMax = positionMax-1;
        
    };
    
    _boutonStatut = true;
    _boutonAvant = true;
    _position = 0;
    _dataAvant = 0;
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

void RoueCodeuseSimple::ReadBoutonAlgorithme()
{
    int boutonRawPos = __ReadDigital(_brocheBouton);
    bool _boutonStatut = (boutonRawPos == 1) ? true : false;
    bool copiedavant = _boutonAvant;
    _boutonAvant = _boutonStatut;
    if(copiedavant != _boutonStatut)
        _boutonPressedCallback(_boutonStatut );
    
}

void RoueCodeuseSimple::Tick(){
    ReadBoutonAlgorithme();
}

void RoueCodeuseSimple::AbonneBoutonChanged(ptFnBoutonStatus callback){
    _boutonPressedCallback = callback;
}