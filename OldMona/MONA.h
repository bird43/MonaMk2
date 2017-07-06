#ifndef MONA_H
#define MONA_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "TimerOne.h"


//activate debugging mode
#define MONA_DEBUG 0 //1 on;0 off

#define motorEnable 7 //1 on;0 off
//MONA motor configuration
//A PWM has to be set on the A or B
//pins for each motor, depending the direction wanted
#define motorLeftA 3 //A+!B->FW
#define motorLeftB 5 //!A+B->BW
#define motorRightA 4 //A+!B->FW
#define motorRightB 6 //!A+B->BW
#define FW 1
#define BW 0

#define topLED 8
#define bottomLED 13

#define intPeriod 100 //default frequency at 100 ms
#define encoderRight 9 //encoder digital inouts
#define encoderLeft 10

#define proxEnable 2 //1 on;0 off
#define proxFront A2
#define proxFRight A1
#define proxFLeft A3



class MONA{
public:
  MONA();

  void initProxSensor(void); //start the proximity sensor IR
  void stopProxSensor(void); //stop the proximity sensor IR
  int16_t readFRSensor(void); //retrieve the Front Right distance sensor
  int16_t readFMSensor(void); //retrieve the Front distance sensor
  int16_t readFLSensor(void); //retrieve the Front Left distance sensor
  void readAllSensors(int16_t *proxSensors); //retrreive all the proximity sensor data in one pointer


  void initMotors(void);//configure the pins of the motors as ouputs
  void setRMotorPWM(uint8_t pwm = 0,boolean dir = FW); //Set Right motor speed and direction
  void setLMotorPWM(uint8_t pwm = 0,boolean dir = FW); //Set Left motor speed and direction

  //encoders use the Timer 1
  void initEncoders(uint32_t period = intPeriod); //begin the encoder pulling routine
  void stopEncoders(void); //stop the encoder pulling routine
  int32_t readREncoder(void); //read the value of the right encoder
  int32_t readLEncoder(void);
  int32_t readREncoderTime(void);
  int32_t readLEncoderTime(void); //read the value of the left EncoderLeft
  void resetREncoder(void); //reset the tick cound for the right encoder
  void resetLEncoder(void); //reset the tick count for the left encoder
  void resetEncoders(void); //reset both encoders' tick counts
  void readEncoders(int32_t *encoders); //read both encoders 
};

#endif //  MONA_H
