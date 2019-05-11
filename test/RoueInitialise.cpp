#include <unity.h>
#include <RoueCodeuseSimple.h>



void DoitEtrePret_Quand_ToutesBrochesConfigured()
{
  //Prepare
  TEST_ASSERT_FALSE(RoueCodeuseSimple::IsReady())  ;
  int pinBouton,pinClock,pinData,osef;
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

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(DoitEtrePret_Quand_ToutesBrochesConfigured);
    RUN_TEST(DoitEtreEnPositionZero_ApresInit);
    UNITY_END();
}

