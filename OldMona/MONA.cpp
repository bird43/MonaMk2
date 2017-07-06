/***************************************************
  This is a library for the MONA educational mobile robot
  Designed specifically to work with the MONA platform
  ----> http://www.mona.uk
  Written by Jose Espinosa/Farshad Arvin for The University of Manchester.
  TODO:ADDlicense
 ****************************************************/
#include "MONA.h"

//variables to store the encoder ticks
volatile long encoderRTicks = 0;
volatile long encoderLTicks = 0;
volatile long encoderLTime = 0;
volatile long encoderRTime = 0;
volatile long TimeNowR = 0;
volatile long TimeNowL = 0;
//variable to read the encoder
volatile boolean encoderR = 0;
volatile boolean encoderL = 0;
volatile boolean encoderROld = 0;
volatile boolean encoderLOld = 0;

//variables to store the direction of the motors
volatile boolean dirR = 0;
volatile boolean dirL = 0;


MONA::MONA(){
}

void MONA::initMotors(void){
  //setup the pin mode for all the motor related pins
  pinMode(motorEnable, OUTPUT);
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  //enable the use of the motors
  digitalWrite(motorEnable,HIGH);
  //halt the motors
  digitalWrite(motorRightA,LOW);
  digitalWrite(motorRightB,LOW);
  digitalWrite(motorLeftA,LOW);
  digitalWrite(motorLeftB,LOW);

}

void MONA::setRMotorPWM(uint8_t pwm,boolean dir){
  dirR = dir;
  if(dir>0){
    pwm = abs(pwm - 255);
    analogWrite(motorRightB,pwm);
    digitalWrite(motorRightA,1);
  }
  else{
    digitalWrite(motorRightA,0);
    analogWrite(motorRightB,pwm);
  }
}

void MONA::setLMotorPWM(uint8_t pwm,boolean dir){
  dirL = dir;
  if(dir>0){
    digitalWrite(motorLeftB,0);
    analogWrite(motorLeftA,pwm);
  }
  else{
    digitalWrite(motorLeftA,0);
    analogWrite(motorLeftB,pwm);
  }
}

void MONA::initProxSensor(void){ //start the proximity sensor IR
  pinMode(proxEnable, OUTPUT); //Enabel IR emiters
  digitalWrite(proxEnable, HIGH); //Enabel IR emiters
}

void MONA::stopProxSensor(void){ //start the proximity sensor IR
  pinMode(proxEnable, LOW); //Disabel IR emiters
}

int16_t MONA::readFRSensor(void){ //retrieve the Front Right distance sensor
  int value = analogRead(proxFRight);
  return value;
}

int16_t MONA::readFMSensor(void){ //retrieve the Front Centre distance sensor
  int value = analogRead(proxFront);
  return value;
}

int16_t MONA::readFLSensor(void){ //retrieve the Front Left distance sensor
  int value = analogRead(proxFLeft);
  return value;
}

void MONA::readAllSensors(int16_t *proxSensors){

  proxSensors[0] = analogRead(proxFRight);
  proxSensors[1] = analogRead(proxFront);
  proxSensors[2] = analogRead(proxFLeft);

}

//read the encoder value
//TODO: try to make it shorter and more efficient
void getETicks(void){
  //read the encoders and store the values
  encoderR = digitalRead(encoderRight);
  encoderL = digitalRead(encoderLeft);
  //compare to see if the value changed from the last interrupt
  if((encoderR != encoderROld) && (encoderR == 1)){
    encoderRTime = millis() - TimeNowR;
    TimeNowR = millis();
    if(dirR == FW)
      encoderRTicks = encoderRTicks + 1;
    else
      encoderRTicks = encoderRTicks - 1;
    }
  if((encoderL != encoderLOld) && (encoderL == 1)){
    encoderLTime = millis() - TimeNowL;
    TimeNowL = millis();
    if(dirL == FW)
      encoderLTicks = encoderLTicks + 1;
    else
      encoderLTicks = encoderLTicks - 1;
    }
  //store the value of the encoders for future reference
  encoderROld = encoderR;
  encoderLOld = encoderL;
}

void MONA::initEncoders(uint32_t period){ //begin the encoder pulling routine wi the period in ms
  //set the encoder pins to inputs
  pinMode(encoderRight,INPUT);
  pinMode(encoderLeft,INPUT);
  TimeNowR = millis();
  TimeNowL = millis();
  //set the period for the timer interrupt
  period = period * 1000;
  Timer1.initialize(period);//value in ms
  //attach the interrupt to the getTicks function
  Timer1.attachInterrupt(getETicks);

}

int32_t MONA::readREncoder(void){ //read the value of the right encoder
  noInterrupts();
  long value = encoderRTicks;
  interrupts();
  return value;
}

int32_t MONA::readREncoderTime(void){ //read the value of the right encoder
  noInterrupts();
  long value = encoderRTime;
  interrupts();
  return value;
}


int32_t MONA::readLEncoder(void){ //read the value of the right encoder
  noInterrupts();
  long value = encoderLTicks;
  interrupts();
  return value;
}

int32_t MONA::readLEncoderTime(void){ //read the value of the right encoder
  noInterrupts();
  long value = encoderLTime;
  interrupts();
  return value;
}

void MONA::readEncoders(int32_t *encoders){//return both encoder values as a pointer
  noInterrupts();
  encoders[0] = encoderRTicks;
  encoders[1] = encoderLTicks;
  interrupts();
}

void MONA::resetREncoder(void){ //reset the tick cound for the right encoder
  noInterrupts();
  encoderRTicks = 0;
  encoderRTime = 0;
  interrupts();
}

void MONA::resetLEncoder(void){ //reset the tick cound for the right encoder
  noInterrupts();
  encoderLTicks = 0;
  encoderLTime = 0;
  interrupts();
}

void MONA::resetEncoders(void){ //reset both ecoders
    noInterrupts();
    encoderLTicks = 0;
    encoderRTicks = 0;
    encoderRTime = 0;
    encoderLTime = 0;
    interrupts();
  }
