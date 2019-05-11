#ifndef ROUE_CODEUSE_SIMPLE_H_
#define ROUE_CODEUSE_SIMPLE_H_

class RoueCodeuseSimple
{
    private:
     static int _brocheBouton;
     static int _brocheData;
     static int _brocheClock;

     static short _position;
     static short _positionMax;
     static bool _boutonStatut;
     static int _dataAvant;

     public:
     static void Initialise(int pinBouton, int pinData, int pinClock,short positionMax);
     static bool IsReady();
     static void Tick();
     static short GetPosition();
     static bool GetBoutonStatut();
};



#endif