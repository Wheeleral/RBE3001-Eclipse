/*
 * GripperServer.cpp
 *
 *  Created on: Oct 5, 2017
 *      Author: awheeler2
 */

#include "GripperServer.h"

void GripperServer::event(float * buffer) {

	//status command that will send position, velocity and torque of the axis.
    float gripperVal        = buffer[0];

    if(gripperVal>0)
    	gripper->write(open);
    else
    	gripper->write(closed);

	uint8_t * buff = (uint8_t *) buffer;
	for (int i = 4; i < 64; i++) {
		buff[i] = 0;
	}

	//printf("\nPid Server Event");
	for (int i = 0; i < myPumberOfPidChannels; i++) {
		float torque = 0;
		float position = myPidObjects[i]->GetPIDPosition();
		float velocity = myPidObjects[i]->getVelocity();

		// write upstream packets
		buffer[(i * 3) + 0] = position;
		buffer[(i * 3) + 1] = velocity;
		buffer[(i * 3) + 2] = torque;

	}

}
