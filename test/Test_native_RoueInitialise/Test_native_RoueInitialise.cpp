#include <unity.h>
#include <RoueCodeuseSimple.h>

 int pinBouton,pinClock,pinData;
 int MockReadPinDigital(uint8_t pin)
{
  return 0;
}




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
  RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,osef);

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
    RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,osef);
    short actuel = RoueCodeuseSimple::GetPosition();
    //Test
    TEST_ASSERT_EQUAL(attendu,actuel);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RoueCodeuseSimple::__ReadDigital = MockReadPinDigital;
    RUN_TEST(DoitEtrePret_Quand_ToutesBrochesConfigured);
    RUN_TEST(DoitEtreEnPositionZero_ApresInit);
    UNITY_END();
}

