#include <MONA.h>

MONA mona;

void setup(){
  
  unsigned char DIR = 0; // either 0 or 1 for forwards and backwards
  unsigned char PWM = 50; // between 0 and 255
  mona.InitMotors();
  mona.DriveRight(PWM, DIR);
  mona.DriveLeft(PWM, DIR);
  mona.InitEncoders();
  Serial.begin(9600);
}

void loop(){
  
  long RightEncoder = 0;
  long LeftEncoder = 0;
  int data[5];
  int battery;
  
  while(1){
      RightEncoder = mona.GetRightEncoder();
      LeftEncoder = mona.GetLeftEncoder();
      mona.EnableIRSensors(); // this can be done once in setup if you wish
      mona.ReturnIRSensorData(data); // this will update the data array
      mona.DisableIRSensors(); // not really required, illustrated if required
      battery = mona.GetBattery();
      
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
      delay(1000);
  }
}

