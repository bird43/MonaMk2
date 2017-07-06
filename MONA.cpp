#include "MONA.h"

//variables to store the encoder ticks
volatile long RightEncoderTicks = 0;
volatile long LeftEncoderTicks = 0;


void LeftEncoderISR(void){
  LeftEncoderTicks++;
}

void RightEncoderISR(void){
  RightEncoderTicks++;
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

float MONA::LeftVelocity(void){ // doesn't work yet
  float TimePeriod;
  float Velocity;

  TimePeriod = LeftTimePeriod();
  Velocity = (WheelCircum / TicksPerRev) / TimePeriod;
  return Velocity;
}

float MONA::RightVelocity(void){ // doesn't work yet, will probably move to ISR and count 100 pulse durations before updating global variable
  double TimePeriod;
  double Velocity;

  TimePeriod = RightTimePeriod();
  Velocity = (DistPerTick / TimePeriod);
  Serial.println(Velocity,8);

  return Velocity;
}