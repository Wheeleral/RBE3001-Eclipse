#include "StatusServer.h"

void StatusServer::event(float * buffer) {

	//status command that will send position, velocity and torque of the axis.

	uint8_t * buff = (uint8_t *) buffer;
	for (int i = 4; i < 64; i++) {
		buff[i] = 0;
	}

	//printf("\nPid Server Event");
	for (int i = 0; i < myPumberOfPidChannels; i++) {
		sum1 -= loadVals1[indexer];
		loadVals1[indexer] = scale1*(100*L1.read()-43.72);
		sum1 += loadVals1[indexer];
		avg1 = sum1 / 10;

		sum2 -= loadVals2[indexer];
		loadVals2[indexer] = scale2*(100*L2.read()-(44.096+2.72));
		sum2 += loadVals2[indexer];
		avg2 = sum2 / 10;

		sum3 -= loadVals3[indexer];
		loadVals3[indexer] = scale3*(100*L3.read()-(47.4+4.62));
		sum3 += loadVals3[indexer];
		avg3 = sum3 / 10;

		indexer = (indexer + 1) % 10;
		float torque = 0;
		float position = myPidObjects[i]->GetPIDPosition();
		float velocity = myPidObjects[i]->getVelocity();
		if (i == 0)
			torque = avg1;
		else if (i == 1)
			torque = avg2;
		else if (i == 2)
			torque = avg3;
		// write upstream packets
		buffer[(i * 3) + 0] = position;
		buffer[(i * 3) + 1] = velocity;
		buffer[(i * 3) + 2] = torque;

	}

}
