#include "RoueCodeuseSimple.h"
#ifdef ARDUINO
    #include <Arduino.h>
#endif


uint8_t RoueCodeuseSimple::_brocheBouton = 0;
uint8_t RoueCodeuseSimple::_brocheData = 0;
uint8_t RoueCodeuseSimple::_brocheClock = 0;
short RoueCodeuseSimple::_position = 0;
short RoueCodeuseSimple::_positionMax = 0;
bool RoueCodeuseSimple::_boutonStatut = true;
bool RoueCodeuseSimple::_boutonAvant = true;
int RoueCodeuseSimple::_clockAvant = 0;
ptFnReadDigital RoueCodeuseSimple::__ReadDigital = 0;

ptFnBoutonStatus RoueCodeuseSimple::_boutonPressedCallback = 0;
ptFnPosChange RoueCodeuseSimple::_positionChangeCallback = 0;

void RoueCodeuseSimple::__ForcePos(int pos)
{
    _position = pos;
}

void   RoueCodeuseSimple::Initialise(uint8_t pinBouton, uint8_t pinData, uint8_t pinClock,short positionMax)
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
    _boutonAvant = 1;
    _position = 0;
   
    _clockAvant = 1;
};

bool  RoueCodeuseSimple::IsReady(){
    return !(_brocheClock == 0 && _brocheData == 0 && _brocheBouton == 0);
}

short  RoueCodeuseSimple::GetPosition(){
    return RoueCodeuseSimple::_position;
};

void RoueCodeuseSimple::IncrementePosition() {
    if(_position == _positionMax)
        _position = 0;
    else
        _position++;
}

void RoueCodeuseSimple::DecrementePosition() {
 if(_position == 0)
        _position = _positionMax;
    else
        _position--;
}

bool  RoueCodeuseSimple::GetBoutonStatut(){
    return RoueCodeuseSimple::_boutonStatut;
};

void RoueCodeuseSimple::ReadBoutonAlgorithme()
{
    int boutonRawPos = __ReadDigital(_brocheBouton);
    bool _boutonStatut = (boutonRawPos == 1) ? true : false;
    bool copiedavant = _boutonAvant;
    _boutonAvant = _boutonStatut;
    if(_boutonPressedCallback && copiedavant != _boutonStatut)
        _boutonPressedCallback(_boutonStatut );
    
}

void  RoueCodeuseSimple::ReadCodeuseAlgorithme()
{
    int clockPos = __ReadDigital(_brocheClock);
    int dataPos = __ReadDigital(_brocheData);
    if(clockPos == _clockAvant)
        return;
    
    _clockAvant = clockPos;
    if(dataPos != clockPos) //Horaire
    {
        IncrementePosition();
        if(_positionChangeCallback)
            _positionChangeCallback(_position,true);
    }
    else //AntiHoraire
    {
        DecrementePosition();
        if(_positionChangeCallback)
            _positionChangeCallback(_position,false);
    }

}

void RoueCodeuseSimple::Tick(){
    ReadBoutonAlgorithme();
    ReadCodeuseAlgorithme();
}

void RoueCodeuseSimple::AbonneBoutonChanged(ptFnBoutonStatus callback){
    _boutonPressedCallback = callback;
}

void RoueCodeuseSimple::AbonnePositionChanged(ptFnPosChange callback) {
    _positionChangeCallback = callback;
}