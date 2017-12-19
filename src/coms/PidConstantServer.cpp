/*
 * PidConstantServer.cpp
 *
 *  Created on: Sep 11, 2017
 *      Author: awheeler2
 *
 *      used for tuning pid and setting the PID values from Matlab
 */
#include "PidConstantServer.h"

void PidConstantServer::event(float * buffer){

  //printf("\nPid Server Event");
  for(int i=0; i<myPumberOfPidChannels;i++){
	 float kp = buffer[(i*3)+0];
	 float ki = buffer[(i*3)+1];
	 float kd = buffer[(i*3)+2];
	 myPidObjects[i]->setPIDConstants(kp, ki, kd); //set pid  for each pidobject


  }
  uint8_t * buff = (uint8_t *)buffer;
  for(int i=4; i<64;i++){
    buff[i]=0;
  }
  //printf("\nPid Server Event");
    for(int i=0; i<myPumberOfPidChannels;i++){ //returns a status command

      float position = myPidObjects[i]->GetPIDPosition();
      float velocity = myPidObjects[i]->getVelocity();;
      float torque = 2.0;
      // write upstream packets
      buffer[(i*3)+0] = position;
      buffer[(i*3)+1] = velocity;
      buffer[(i*3)+2] = torque;

    }
}




