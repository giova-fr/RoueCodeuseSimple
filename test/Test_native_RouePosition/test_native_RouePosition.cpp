#include <unity.h>
#include <RoueCodeuseSimple.h>

 int pinBouton,pinClock,pinData;
 int MockReadPinDigital(uint8_t pin)
{
  return 1;
}

int lastSimulatedData, lastSimulatedClock = 0;

int SimuleHoraire(uint8_t pin)
{
    if(pin == pinClock)
    {
        lastSimulatedClock = lastSimulatedClock ? 0 : 1;
        return lastSimulatedClock;
    }
    if(pin == pinData)
    {
        return lastSimulatedClock;
    }
    return 1;
}

int SimuleAntiHoraire(uint8_t pin)
{
    if(pin == pinClock)
    {
        lastSimulatedClock = lastSimulatedClock ? 0 : 1;
        return lastSimulatedClock;
    }
    if(pin == pinData)
    {
        return lastSimulatedClock ? 0 : 1;
    }
    return 1;
}

int SimuleImmobile(uint8_t pin)
{
    if(pin == pinClock)
    {
        return lastSimulatedClock;
    }
    if(pin == pinData)
    {
        return lastSimulatedClock; //On se moque de la valeur car la clock n'a pas bougé
    }
    return 1;
}

void DoitIncrementerPosition_SiHoraire()
{
   

  //Prepare;
  RoueCodeuseSimple::__ReadDigital = SimuleHoraire;
  lastSimulatedClock = SimuleHoraire(pinClock);
  RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,4);
  
  RoueCodeuseSimple::__ForcePos(1);
  int attendu  = RoueCodeuseSimple::GetPosition() + 1;
  
  //Act
  RoueCodeuseSimple::Tick();
  int actuel = RoueCodeuseSimple::GetPosition();
  
   //Test
  TEST_ASSERT_EQUAL(attendu,actuel);
}

void DoitDecrementerPosition_SiAntiHoraire()
{
   

  //Prepare;
  RoueCodeuseSimple::__ReadDigital = SimuleAntiHoraire;
  lastSimulatedClock = SimuleHoraire(pinClock);
  RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,4);
  
  RoueCodeuseSimple::__ForcePos(2);
  int attendu  = RoueCodeuseSimple::GetPosition() - 1;
  
  //Act
  RoueCodeuseSimple::Tick();
  int actuel = RoueCodeuseSimple::GetPosition();
  
   //Test
  TEST_ASSERT_EQUAL(attendu,actuel);
}

void DoitBouclerSur_MaxPos_QuandDecrementeZero()
{
    //Prepare
    int nbrpos = 4;
    RoueCodeuseSimple::__ReadDigital = SimuleAntiHoraire;
    lastSimulatedClock = SimuleHoraire(pinClock);
    RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,nbrpos);
    
    RoueCodeuseSimple::__ForcePos(0);
    int attendu = nbrpos -1 ; //car premiere position à 0 et non à 1

    //Act
    RoueCodeuseSimple::Tick();
    int actuel = RoueCodeuseSimple::GetPosition();
  
    //Test
    TEST_ASSERT_EQUAL(attendu,actuel);


}

void DoitBouclerSur_Zero_QuandIncrementeMaxPos()
{
    //Prepare
    int nbrpos = 4;
    RoueCodeuseSimple::__ReadDigital = SimuleHoraire;
    lastSimulatedClock = SimuleHoraire(pinClock);
    RoueCodeuseSimple::Initialise(pinBouton,true,pinData,pinClock,nbrpos);
    
    RoueCodeuseSimple::__ForcePos(nbrpos-1); //car premiere position à 0 et non à 1
    int attendu = 0 ; 

    //Act
    RoueCodeuseSimple::Tick();
    int actuel = RoueCodeuseSimple::GetPosition();
  
    //Test
    TEST_ASSERT_EQUAL(attendu,actuel);


}

int positionDansCallBack;
bool isHoraireDansCallBack;
int countCallbackPosAppels = 0;

void callbackPosition(int pos,bool isHoraire) {
    positionDansCallBack = pos;
    isHoraireDansCallBack = isHoraire;
    countCallbackPosAppels++;
}

void DoitAppellerCallbackQuandBougeHorraire()
{
    //Prepare
    
    RoueCodeuseSimple::__ReadDigital = SimuleHoraire;
    RoueCodeuseSimple::AbonnePositionChanged(callbackPosition);

    countCallbackPosAppels = 0;
    int attendu = 1;

    //Act
    RoueCodeuseSimple::Tick();

    //Test
    TEST_ASSERT_EQUAL(attendu,countCallbackPosAppels);
}

void NeDoitPasAppellerCallbackQuandNeBougePas()
{
    RoueCodeuseSimple::__ReadDigital = SimuleImmobile;
    RoueCodeuseSimple::AbonnePositionChanged(callbackPosition);

    countCallbackPosAppels = 0;
    int attendu = 0;

    //Act
    RoueCodeuseSimple::Tick();

    //Test
    TEST_ASSERT_EQUAL(attendu,countCallbackPosAppels);
}

void DoitAppellerCallbackQuandBougeAntiHorraire()
{
    //Prepare
    RoueCodeuseSimple::__ReadDigital = SimuleAntiHoraire;
    RoueCodeuseSimple::AbonnePositionChanged(callbackPosition);
  
    countCallbackPosAppels = 0;
    int attendu = 1;

    //Act
    RoueCodeuseSimple::Tick();

    //Test
    TEST_ASSERT_EQUAL(attendu,countCallbackPosAppels);
}

void DoitFournirSensDansCallBack_LorsqueHoraire()
{
    //Prepare
    RoueCodeuseSimple::__ReadDigital = SimuleHoraire;
    RoueCodeuseSimple::AbonnePositionChanged(callbackPosition);

    int posAvant = RoueCodeuseSimple::GetPosition();
    positionDansCallBack = posAvant;
    isHoraireDansCallBack = false; //je fausse expres

    //Act
    RoueCodeuseSimple::Tick();

    //Test
    TEST_ASSERT_NOT_EQUAL(posAvant,positionDansCallBack);
    TEST_ASSERT_TRUE(isHoraireDansCallBack);

}

void DoitFournirSensDansCallBack_LorsqueAntiHoraire()
{
    //Prepare
    RoueCodeuseSimple::__ReadDigital = SimuleAntiHoraire;
    RoueCodeuseSimple::AbonnePositionChanged(callbackPosition);

    int posAvant = RoueCodeuseSimple::GetPosition();
    positionDansCallBack = posAvant;
    isHoraireDansCallBack = true; //je fausse expres

    //Act
    RoueCodeuseSimple::Tick();

    //Test
    TEST_ASSERT_NOT_EQUAL(posAvant,positionDansCallBack);
    TEST_ASSERT_FALSE(isHoraireDansCallBack);

}



int main( int argc, char **argv) {
    pinBouton = 1;
    pinClock = 2;
    pinData = 3;
    RoueCodeuseSimple::__ReadDigital = MockReadPinDigital;
    UNITY_BEGIN();
    
    RUN_TEST(DoitIncrementerPosition_SiHoraire);
    RUN_TEST(DoitDecrementerPosition_SiAntiHoraire);
    RUN_TEST(DoitBouclerSur_MaxPos_QuandDecrementeZero);
    RUN_TEST(DoitBouclerSur_Zero_QuandIncrementeMaxPos);
    RUN_TEST(DoitAppellerCallbackQuandBougeHorraire);
    RUN_TEST(NeDoitPasAppellerCallbackQuandNeBougePas);
    RUN_TEST(DoitAppellerCallbackQuandBougeAntiHorraire);
    RUN_TEST(DoitFournirSensDansCallBack_LorsqueHoraire);
    RUN_TEST(DoitFournirSensDansCallBack_LorsqueAntiHoraire);

    UNITY_END();
}

