// Benjamin Bird 
// Robotics PhD Student - University of Manchester 
// United Kingdom

//#define USE_USBCON
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <MONA.h>
#define RovWid 0.24 //////////////////////////////////////// change me

MONA mona;
ros::NodeHandle  nh;
std_msgs::Float32 tick_msg_left;
std_msgs::Float32 tick_msg_right;
geometry_msgs::Twist msg;
ros::Publisher pub_tick_left("ticks_left", &tick_msg_left);
ros::Publisher pub_tick_right("ticks_right", &tick_msg_right);

float XVel, Heading;

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{
  XVel = cmd_vel.linear.x;
  Heading = cmd_vel.angular.z;
}

ros::Subscriber <geometry_msgs::Twist> sub("/turtle1/cmd_vel",roverCallBack);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_tick_left); 
  nh.advertise(pub_tick_right);
  mona.InitMotors();
  mona.InitEncoders();
}

void loop() {
  long RightEncoder = 0;
  long LeftEncoder = 0;
  long LeftTime = 0;
  long RightTime = 0;
  long OdomLeft = 0;
  long OdomRight = 0;
  int data[5];
  int battery;
  float LeftVelocity, RightVelocity;
  char PWML = 0;
  char DIRL = 0;
  char PWMR = 0;
  char DIRR = 0;

  while(1){
    OdomLeft = mona.GetLeftOdom();
    OdomRight = mona.GetRightOdom();
    tick_msg_left.data = OdomLeft;
    tick_msg_right.data = OdomRight;
    pub_tick_left.publish(&tick_msg_left);
    pub_tick_right.publish(&tick_msg_right);
    
    mona.DriveRight(PWMR, DIRR);
    mona.DriveLeft(PWML, DIRL);
    
    delay(10);
    nh.spinOnce();
  }
}


