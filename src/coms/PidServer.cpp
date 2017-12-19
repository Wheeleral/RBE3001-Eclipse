#include "PidServer.h"

void PidServer::event(float * buffer){

  //printf("\nPid Server Event");
  bool skipLink = false;
  for(int i=0; i<myPumberOfPidChannels;i++){

    float position = myPidObjects[i]->GetPIDPosition(); //get position for each pidobject

    // read values from the packet buffer
    float setpoint        = buffer[(i*3)+0];
    float velocityTarget  = buffer[(i*3)+1];
    float forceTarget     = buffer[(i*3)+2];

    //perform state update
    float timeOfMotion=0;
    if(velocityTarget>0)
     timeOfMotion=(std::abs(setpoint-position)/velocityTarget)*1000;// convert from Tics per second to miliseconds
    bool newUpdate = !myPidObjects[i]->bound(setpoint,
      myPidObjects[i]->state.interpolate.set,
      0.01,
     0.01);

    if(newUpdate){

      __disable_irq();    // Disable Interrupts
      myPidObjects[i]->SetPIDEnabled( true);
      myPidObjects[i]->SetPIDTimed(setpoint, timeOfMotion);// go to setpoint in timeBetweenPrints ms, linear interpolation
      __enable_irq();

   }else{
    //  printf("\r\nPacket write ignored, index %i to %f is already %f",i,setpoint,myPidObjects[i]->state.interpolate.set);
     skipLink=true;
   }

  }
  uint8_t * buff = (uint8_t *)buffer;
  for(int i=4; i<64;i++){
    buff[i]=0;
  }
  //printf("\nPid Server Event");
  for(int i=0; i<myPumberOfPidChannels;i++){

    float position = myPidObjects[i]->GetPIDPosition();
    float velocity =0;//myPidObjects[i]->getVelocity();
    float torque = 0;
    // write upstream packets
    buffer[(i*3)+0] = position;
    buffer[(i*3)+1] = velocity;
    buffer[(i*3)+2] = torque;

  }

}
