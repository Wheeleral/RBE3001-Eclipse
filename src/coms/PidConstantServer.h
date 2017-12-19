/*
 * PidConstantServer.h
 *
 *  Created on: Sep 11, 2017
 *      Author: awheeler2
 *
 *      Copied form pidServer
 */



#ifndef  Pid_CServer
#define Pid_CServer
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs
#define PidCServerID 55

class PidConstantServer: public PacketEventAbstract{
private:
  PIDBowler* * myPidObjects;
   int myPumberOfPidChannels;
public:
   PidConstantServer (PIDBowler* * pidObjects, int numberOfPidChannels ) : PacketEventAbstract(PidCServerID){
	 myPidObjects=pidObjects;
	 myPumberOfPidChannels=numberOfPidChannels;
}

  void event(float * buffer);
};

#endif
 /* end of include guard: Pid_server */

