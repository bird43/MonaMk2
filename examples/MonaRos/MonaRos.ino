// Benjamin Bird 
// Robotics PhD Student - University of Manchester 
// United Kingdom

//#define USE_USBCON
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <MONA.h>
#define RovWid 0.086 

MONA mona;
ros::NodeHandle  nh;
std_msgs::Float32 tick_msg_left;
std_msgs::Float32 tick_msg_right;
geometry_msgs::Twist msg;
ros::Publisher pub_tick_left("ticks_left", &tick_msg_left);
ros::Publisher pub_tick_right("ticks_right", &tick_msg_right);


float DesVelRight, DesVelLeft;

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{
  float XVel, Heading;
  XVel = cmd_vel.linear.x;
  Heading = cmd_vel.angular.z;
  DesVelRight = (2 * XVel + (Heading * RovWid)) / 2;
  DesVelLeft = (2 * XVel - (Heading * RovWid)) / 2; // turn this into 
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel",roverCallBack); // changeback to /turtle1/cmd_vel to use standard turtlesim teleop keyu thingy

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_tick_left); 
  nh.advertise(pub_tick_right);
  mona.InitMotors();
  mona.InitEncoders();
}

void loop() {
  //long RightEncoder = 0;
  //long LeftEncoder = 0;
  //long LeftTime = 0;
  //long RightTime = 0;
  long OdomLeft = 0;
  long OdomRight = 0;
  //int data[5];
  //int battery;
  //float LeftVelocity, RightVelocity;
  unsigned char PWML = 0;
  unsigned char DIRL = 0;
  unsigned char PWMR = 0;
  unsigned char DIRR = 0;

  while(1){
    OdomLeft = mona.GetLeftOdom();
    OdomRight = mona.GetRightOdom();
    tick_msg_left.data = OdomLeft;
    tick_msg_right.data = OdomRight;
    pub_tick_left.publish(&tick_msg_left);
    pub_tick_right.publish(&tick_msg_right);

    if(DesVelRight >= 0){
      DIRR = 0;
      PWMR = 2466*(DesVelRight*DesVelRight) + 229.1 * DesVelRight + 28.51;
    }
    else{
      DIRR = 1;
      PWMR = -819 * (DesVelRight*DesVelRight) - 1106 * DesVelRight + 23.71;
    }
    if(DesVelLeft >=  0){
      DIRL = 0;
      PWML = 2705 * (DesVelLeft*DesVelLeft) + 257.9 * DesVelLeft + 26.64;
    }
    else{
      DIRL = 1;
      PWML = -803.9 * (DesVelLeft*DesVelLeft) - 1124 * DesVelLeft + 23.61;
    }
    
    if(DesVelRight == 0.0){
      PWMR = 0;
    }
    if(DesVelLeft == 0.0){
      PWML = 0;
    }
    
    mona.DriveRight(PWMR, DIRR);
    mona.DriveLeft(PWML, DIRL);

    delay(10);
    nh.spinOnce();
  }
}


