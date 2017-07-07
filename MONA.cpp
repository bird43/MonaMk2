#include "MONA.h"

//variables to store the encoder ticks
volatile long RightEncoderTicks = 0;
volatile long LeftEncoderTicks = 0;
double LVel = 0;
double RVel = 0;
char LCounter = 0;
char RCounter = 0;
long TimeNowLeft = 0;
long TimeNowRight = 0;
long TimeStartLeft = 0;
long TimeStartRight = 0;

void LeftEncoderISR(void){
  LeftEncoderTicks++;
  LCounter++;
  if(LCounter == 1){
    TimeStartLeft = micros();
  }
  if(LCounter == 11){
    LCounter = 0;
    TimeNowLeft = micros() - TimeStartLeft;

    LVel = 0.0009387755 / (float (TimeNowLeft) / 1000000);
  }
}

void RightEncoderISR(void){
  RightEncoderTicks++;
  RCounter++;
  if(RCounter == 1){
    TimeStartRight = micros();
  }
  if(RCounter == 11){
    RCounter = 0;
    TimeNowRight = micros() - TimeStartRight;

    RVel = 0.0009387755 / (float (TimeNowRight) / 1000000);
  }
}

MONA::MONA(){
}

void MONA::InitMotors(void){
  pinMode(PWMRight, OUTPUT);
  pinMode(PWMLeft, OUTPUT);
  pinMode(DIRRight, OUTPUT);
  pinMode(DIRLeft, OUTPUT);
  digitalWrite(DIRRight, LOW);
  digitalWrite(DIRLeft, LOW);
  digitalWrite(PWMRight, LOW);
  digitalWrite(PWMLeft, LOW);
}

void MONA::DriveRight(unsigned char PWM, unsigned char DIR){
  if(DIR == 1){
    digitalWrite(DIRRight, HIGH);
    analogWrite(!PWMRight, PWM);
  }
  else{
    digitalWrite(DIRRight, LOW);
    analogWrite(PWMRight, PWM);
  }
  
}

void MONA::DriveLeft(unsigned char PWM, unsigned char DIR){
  if(DIR == 1){
    digitalWrite(DIRLeft, HIGH);
    analogWrite(!PWMLeft, PWM);
  }
  else{
    digitalWrite(DIRLeft, LOW);
    analogWrite(PWMLeft, PWM);
  }
  
}

void MONA::EnableIRSensors(void){
  pinMode(IREN, OUTPUT);
  digitalWrite(IREN, HIGH);
}

void MONA::DisableIRSensors(void){
  pinMode(IREN, OUTPUT);
  digitalWrite(IREN, LOW);
}

void MONA::ReturnIRSensorData(int *data){ // couldn't get it to relaibaly return pointer to array so
  data[0] = analogRead(IRRight);          // passing pointer into fucntion instead
  data[1] = analogRead(IRFrontRight);
  data[2] = analogRead(IRFront);
  data[3] = analogRead(IRFrontLeft);
  data[4] = analogRead(IRLeft);
}

void MONA::InitEncoders(void){
  attachInterrupt(digitalPinToInterrupt(ENCLeft), LeftEncoderISR, HIGH);
  attachInterrupt(digitalPinToInterrupt(ENCRight), RightEncoderISR, HIGH);
}


long MONA::GetRightEncoder(void){
  return RightEncoderTicks;
}

long MONA::GetLeftEncoder(void){
  return LeftEncoderTicks;
}

int MONA::GetBattery(void){
  return analogRead(Batt); 
}

long MONA::LeftTimePeriod(void){
  return pulseIn(ENCLeft, HIGH);
}

long MONA::RightTimePeriod(void){
  return pulseIn(ENCRight, HIGH);
}

float MONA::LeftVelocity(void){
  return LVel;
}

float MONA::RightVelocity(void){ // doesn't work yet, will probably move to ISR and count 100 pulse durations before updating global variable
  return RVel;
}