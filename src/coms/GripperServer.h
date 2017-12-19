/*
 * GripperServer.h
 *
 *  Created on: Oct 5, 2017
 *      Author: awheeler2
 */

#ifndef SRC_COMS_GRIPPERSERVER_H_
#define SRC_COMS_GRIPPERSERVER_H_
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include "mbed.h"
#include "Servo.h"
#include "../mbed-os/targets/TARGET_STM/TARGET_STM32F7/TARGET_STM32F746xG/TARGET_NUCLEO_F746ZG/PinNames.h"
#include "../mbed-os/drivers/AnalogIn.h"
#include "../mbed-os/drivers/AnalogOut.h"
#include <cmath>        // std::abs
#define GripperServerID 5  //the universe

class GripperServer: public PacketEventAbstract{
private:
  PIDBowler* * myPidObjects;
   int myPumberOfPidChannels;
   PinName gripperPin;
   Servo  * gripper;
   float open = 0;
   float closed = 1;

public:
  // Packet ID needs to be set
   GripperServer (PIDBowler* * pidObjects, int numberOfPidChannels, PinName gripPin, Servo * mygripper): PacketEventAbstract( GripperServerID){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
    gripperPin= gripPin;
    gripper = mygripper;

  }

  void event(float * buffer);
};
#endif /* SRC_COMS_GRIPPERSERVER_H_ */
