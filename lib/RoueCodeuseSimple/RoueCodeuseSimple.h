#ifndef ROUE_CODEUSE_SIMPLE_H_
#define ROUE_CODEUSE_SIMPLE_H_
typedef void (*ptFnBoutonStatus)(bool);
typedef int (*ptFnReadDigital)(int);

class RoueCodeuseSimple
{
    private:
     static int _brocheBouton;
     static int _brocheData;
     static int _brocheClock;

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

     public:
     static ptFnReadDigital __ReadDigital;
     static void __ForcePos(int pos);
     static void Initialise(int pinBouton, int pinData, int pinClock,short positionMax);
     static bool IsReady();
     static void Tick();
     static short GetPosition();
     static bool GetBoutonStatut();
     static void AbonneBoutonChanged(ptFnBoutonStatus callback);
     
};



#endif