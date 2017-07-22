//include the robot's header file
#include <MONA.h>
//initialise an object calle mona using the MONA structure
MONA mona;
int lapse = 0;
long right_encoder = 0;
long left_encoder = 0;
long right_encoder_time = 0;
long left_encoder_time = 0;

void setup() {
  Serial.begin(9600);
  mona.InitMotors();
  mona.InitEncoders();
  delay(5000);
  Serial.println("test starting");
}

void loop() {

  while(1){

    for(int i = 0; i<260; i=i+5){
        mona.DriveRight(i, 0);
        mona.DriveLeft(i, 0);
        delay(1000); // allow for intertia
        mona.ResetEncoders();
        delay(1000);//count encoder ticks for 10 seconds
        right_encoder = mona.GetRightEncoder();
        left_encoder = mona.GetLeftEncoder();
        left_encoder_time = mona.LeftTimePeriod();
        right_encoder_time = mona.RightTimePeriod();
        Serial.println(right_encoder);
        Serial.println(left_encoder);
        Serial.println(right_encoder_time);
        Serial.println(left_encoder_time);
    }
    

    for(int i = 0; i<260; i=i+5){
        mona.DriveRight(i, 1);
        mona.DriveLeft(i, 1);
        delay(1000); // allow for intertia
        mona.ResetEncoders();
        delay(1000);//count encoder ticks for 10 seconds
        right_encoder = mona.GetRightEncoder();
        left_encoder = mona.GetLeftEncoder();
        left_encoder_time = mona.LeftTimePeriod();
        right_encoder_time = mona.RightTimePeriod();
        Serial.println(right_encoder);
        Serial.println(left_encoder);
        Serial.println(right_encoder_time);
        Serial.println(left_encoder_time);
        
    }
    mona.DriveRight(0, 1);
    mona.DriveLeft(0, 1);
    while(1){}
    }

}
