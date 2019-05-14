#include <unity.h>
#include <RoueCodeuseSimple.h>

 int pinBouton,pinClock,pinData;

int MockReadPinDigital(uint8_t pin)
{
  return 1;
}



int SimuleBoutonMaintenuPressed(uint8_t pin)
{
    if(pin == pinBouton)
      return 0;
    //default;
    return 100;
}

bool lastbtpos = true;

int SimuleBoutonInverse(uint8_t pin)
{
  
  if(pin == pinBouton)
  {
    lastbtpos = !lastbtpos;
    return (int)lastbtpos;
  }
  //default;
  return 100;
      
}


int StubBoutonPos = -1;
int nbrAppelCallbackBouton = 0;

void StubCallbackBouton(bool btPos)
{
  nbrAppelCallbackBouton++;
  btPos ? StubBoutonPos = 1 : StubBoutonPos = 0;
  
}

void DoitAppellerCallbackLorsqueBoutonPressed()
{
   

  //Prepare;
  RoueCodeuseSimple::__ReadDigital = SimuleBoutonMaintenuPressed;
  RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,4);
  RoueCodeuseSimple::AbonneBoutonChanged(StubCallbackBouton);
  StubBoutonPos = -1;
  int attendu  = 0;

  //Act
  //Simule 2 coups d'horloge
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();

  //Test
  TEST_ASSERT_EQUAL(attendu, StubBoutonPos);
}

void DoitAppellerCallbackBouton_UniquementSiIlChangePosition()
{

  //Prepare test bouton maintenu
  nbrAppelCallbackBouton = 0;
  RoueCodeuseSimple::__ReadDigital = SimuleBoutonMaintenuPressed;
  RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,4);
  
  RoueCodeuseSimple::AbonneBoutonChanged(StubCallbackBouton);
  int attenduNbrAppels = 1;

   //Act
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();

  //Test
  TEST_ASSERT_EQUAL(attenduNbrAppels,nbrAppelCallbackBouton);
  
  //Prepare test bouton press puis relache 2 fois
  RoueCodeuseSimple::__ReadDigital = SimuleBoutonInverse;
  attenduNbrAppels = 4;
  
  //Act
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();

  //Test
  TEST_ASSERT_EQUAL(attenduNbrAppels,nbrAppelCallbackBouton);


  
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    
    pinBouton = 1;
    pinClock = 2;
    pinData = 3;
    RoueCodeuseSimple::__ReadDigital  = MockReadPinDigital;
    RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,4);

    RUN_TEST(DoitAppellerCallbackLorsqueBoutonPressed);
    RUN_TEST(DoitAppellerCallbackBouton_UniquementSiIlChangePosition);

    UNITY_END();
}

