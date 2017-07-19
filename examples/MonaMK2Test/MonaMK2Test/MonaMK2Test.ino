#include <MONA.h>

MONA mona;

void setup(){
  
  mona.InitMotors();
  mona.InitEncoders();
  Serial.begin(9600);
}

void loop(){
  
  long RightEncoder = 0;
  long LeftEncoder = 0;
  long LeftTime = 0;
  long RightTime = 0;
  long OdomLeft = 0;
  int data[5];
  int battery;
  float LeftVelocity, RightVelocity;
  unsigned char DIR = 0; // either 0 or 1 for forwards and backwards
  unsigned char PWM = 0; // between 0 and 255
  while(1){
      
      //RightEncoder = mona.GetRightEncoder();
      //LeftEncoder = mona.GetLeftEncoder();
      //mona.EnableIRSensors(); // this can be done once in setup if you wish
      //mona.ReturnIRSensorData(data); // this will update the data array
      //mona.DisableIRSensors(); // not really required, illustrated if required
      //battery = mona.GetBattery();
      //LeftTime = mona.LeftTimePeriod();
      //RightTime = mona.RightTimePeriod();
      //LeftVelocity = mona.LeftVelocity();
      //RightVelocity = mona.RightVelocity();

      for(PWM = 0; PWM<250; PWM=PWM+50){
        DIR = 0;
        mona.DriveLeft(PWM,DIR);
        delay(1000);
        OdomLeft = mona.GetLeftOdom();
        Serial.print(PWM);
        Serial.print("  ");
        Serial.print(DIR);
        Serial.print("  ");
        Serial.println(OdomLeft); 
      }
      
      for(PWM = 0; PWM<250; PWM=PWM+50){
        DIR = 1;
        mona.DriveLeft(PWM,DIR);
        delay(1000);
        OdomLeft = mona.GetLeftOdom();
        Serial.print(PWM);
        Serial.print("  ");
        Serial.print(DIR);
        Serial.print("  ");
        Serial.println(OdomLeft); 
      }
      
      /*
      Serial.print("IR sensor data = ");
      for (int i = 0; i < 5; i++){
        Serial.print(data[i]);
        Serial.print("    ");
      }
      
      Serial.println("  ");
      Serial.print("Battery level = ");
      Serial.println(battery);
      Serial.println("  ");
      
      Serial.print("Right Encoder = ");
      Serial.println(RightEncoder);
      Serial.print("Left Encoder = ");
      Serial.println(LeftEncoder);
      
      Serial.print("Right time in microseconds  ");
      Serial.println(RightTime);
      Serial.print("Leftt time in microseconds  ");
      Serial.println(LeftTime);

      Serial.print("Right velocity  ");
      Serial.print((float)(RightVelocity),4);
      Serial.print("Leftt velocity  ");
      Serial.println((float)(LeftVelocity),4);
     */ 
  }
}

