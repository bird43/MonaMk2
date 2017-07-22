#ifndef MONA_H
#define MONA_H

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TimerOne.h"

#define PWMRight 6
#define PWMLeft 5
#define DIRRight 10
#define DIRLeft 9

#define ENCLeft 2
#define ENCRight 3

#define IREN 4
#define IRRight A7
#define IRFrontRight A0
#define IRFront A1
#define IRFrontLeft A2
#define IRLeft A3

#define LED1 13
#define LED2 12

#define Batt A6

#define WheelCircum 0.092
#define TicksPerRev 980 // from testing, might be plus or minus a few ticks
#define DistPerTick 0.00009387755


void RightEncoderISR(void);
void LeftEncoderISR(void);

class MONA{
public:
	MONA();
	
	void InitMotors(void);
	void DriveRight(unsigned char PWM, unsigned char DIR);
	void DriveLeft(unsigned char PWM, unsigned char DIR);
	void EnableIRSensors(void);
	void DisableIRSensors(void);
	void ReturnIRSensorData(int *data);
	void InitEncoders(void);
	long GetRightEncoder(void);
	long GetLeftEncoder(void);
	void ResetEncoders(void);
	int GetBattery(void);
	long LeftTimePeriod(void);
	long RightTimePeriod(void);
	float LeftVelocity(void);
	float RightVelocity(void);
	long GetRightOdom(void);
	long GetLeftOdom(void);
};

#endif //  MONA_H
