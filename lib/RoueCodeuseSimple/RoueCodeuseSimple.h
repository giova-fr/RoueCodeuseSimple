#ifndef ROUE_CODEUSE_SIMPLE_H_
#define ROUE_CODEUSE_SIMPLE_H_
#include <stdint.h>

typedef void (*ptFnBoutonStatus)(bool);
typedef void (*ptFnPosChange)(int,bool);
typedef int (*ptFnReadDigital)(uint8_t);

class RoueCodeuseSimple
{
    private:
     static uint8_t _brocheBouton;
     static uint8_t _brocheData;
     static uint8_t _brocheClock;

     static short _position;
     static short _positionMax;
     static bool _boutonStatut;
     static int _clockAvant;
     static bool _boutonAvant;

     static void ReadBoutonAlgorithme();
     static void ReadCodeuseAlgorithme();
     static void IncrementePosition();
     static void DecrementePosition();
    

     //Callbacks
     static ptFnBoutonStatus _boutonPressedCallback;
     static ptFnPosChange _positionChangeCallback;

     public:
     static ptFnReadDigital __ReadDigital;
     static void __ForcePos(int pos);
     static void Initialise(uint8_t pinBouton, bool pullup, uint8_t pinData, uint8_t pinClock,short positionMax);
     static bool IsReady();
     static void Tick();
     static short GetPosition();
     static bool GetBoutonStatut();
     static void AbonneBoutonChanged(ptFnBoutonStatus callback);
     static void AbonnePositionChanged(ptFnPosChange callback);
     
};



#endif