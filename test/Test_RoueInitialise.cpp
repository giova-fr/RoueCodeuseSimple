#include <unity.h>
#include <RoueCodeuseSimple.h>

 int pinBouton,pinClock,pinData;

void DoitEtrePret_Quand_ToutesBrochesConfigured()
{
  //Prepare
  TEST_ASSERT_FALSE(RoueCodeuseSimple::IsReady())  ;
  int osef;
  pinBouton = 1;
  pinClock = 2;
  pinData = 3;
  osef = 0;

  //Act
  RoueCodeuseSimple::Initialise(pinBouton,pinData,pinClock,osef);

  //Test
  TEST_ASSERT_TRUE(RoueCodeuseSimple::IsReady());

}

void DoitEtreEnPositionZero_ApresInit()
{
    //Prepare
    int pinBouton,pinClock,pinData,osef;
    pinBouton = 1;
    pinClock = 2;
    pinData = 3;
    osef = 0;

    short attendu = 0;

    //Act
    RoueCodeuseSimple::Initialise(pinBouton,pinData,pinClock,osef);
    short actuel = RoueCodeuseSimple::GetPosition();
    //Test
    TEST_ASSERT_EQUAL(attendu,actuel);
}

int simuleLastclock = 0;

int SimuleCranHoraireEtBoutonPressed(int pin)
{
  if(pin == pinData)
  {
    simuleLastclock = !simuleLastclock;
    return simuleLastclock;
  }
    return 1;
  if(pin == pinClock)
    return 0;

  if(pin == pinBouton)
    return 0;
}


int StubBoutonPos = -1;
int nbrAppelCallbackBouton = 0;

void StubCallbackBouton(bool btPos)
{
  btPos ? StubBoutonPos = 1 : StubBoutonPos = 0;
  nbrAppelCallbackBouton++;
}

void DoitAppellerCallbackLorsqueBoutonPressed()
{
  //Prepare;
  RoueCodeuseSimple::__ReadDigital = SimuleCranHoraireEtBoutonPressed;
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
  //Prepare 
  nbrAppelCallbackBouton = 0;
  RoueCodeuseSimple::__ReadDigital = SimuleCranHoraireEtBoutonPressed;
  RoueCodeuseSimple::AbonneBoutonChanged(StubCallbackBouton);
  int attenduNbrAppels = 1;

   //Simule 2 coups d'horloge
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();
  RoueCodeuseSimple::Tick();

  TEST_ASSERT_EQUAL(attenduNbrAppels,nbrAppelCallbackBouton);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(DoitAppellerCallbackLorsqueBoutonPressed);
    RUN_TEST(DoitEtrePret_Quand_ToutesBrochesConfigured);
    RUN_TEST(DoitEtreEnPositionZero_ApresInit);
    RUN_TEST(DoitAppellerCallbackBouton_UniquementSiIlChangePosition);
    UNITY_END();
}

