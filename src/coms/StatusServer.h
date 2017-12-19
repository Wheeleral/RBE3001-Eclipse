#ifndef  Status_server
#define Status_server
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include "mbed.h"
#include "../mbed-os/targets/TARGET_STM/TARGET_STM32F7/TARGET_STM32F746xG/TARGET_NUCLEO_F746ZG/PinNames.h"
#include "../mbed-os/drivers/AnalogIn.h"
#include "../mbed-os/drivers/AnalogOut.h"
#include <cmath>        // std::abs
#define StatusServerID 42  //the universe

class StatusServer: public PacketEventAbstract{
private:
  PIDBowler* * myPidObjects;
   int myPumberOfPidChannels;
   PinName pin1;
   PinName pin2;
   PinName pin3;
   AnalogIn L1;
   AnalogIn L2;
   AnalogIn L3;
   float loadVals1[10], loadVals2[10], loadVals3[10];
   float sum1, sum2, sum3;
   float avg1, avg2, avg3;
   int indexer;
   float scale1, scale2, scale3;
public:
  // Packet ID needs to be set
   StatusServer (PIDBowler* * pidObjects, int numberOfPidChannels, PinName P1, PinName P2 , PinName P3  )
   : PacketEventAbstract( StatusServerID),L1(P1), L2(P2), L3(P3), loadVals1({0,0,0,0,0,0,0,0,0,0}), loadVals2({0,0,0,0,0,0,0,0,0,0}), loadVals3({0,0,0,0,0,0,0,0,0,0}){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
    pin1=P1;
    pin2=P2;
    pin3=P3;
    indexer=0;
    sum1=0.0;
    sum2=0.0;
    sum3=0.0;
    avg1=avg2=avg3=0.0;
    scale1=1.0;
    scale2=1.0;
    scale3=1.0;
  }

  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
