#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <cmath>
#include "jetracer/jetRacerCar.h"


ros::Publisher joyController;
float throttleMax;
float steerAngleMax;
int throttleAxis;
int steerAxis;
int killSwitchButton;

void joyCallback(const sensor_msgs::Joy::ConstPtr& joyMsg)
{
    float throttle;
    float angle;

	ROS_INFO("GOT MESSAGE");

    throttle   = throttleMax*joy->axes[throttleAxis];
    steerAngle = steerAngleMax*joy->axes[steerAxis];

    jetracer::jetRacerCar carMsg;

     carMsg->throttle = throttle;
     carMsg->steerAngle = steerAngle;

     if(joy->buttons[killSwitchButton]){
	carMsg->throttle = 0;
        carMsg->steerAngle =0;
     }

     joyController.publish(carMsg);
}


int main(int argc, char** argv)
{

   ros::init(argc,argv,"jetRacer_joy");
   ros::NodeHandle node;

   node.getParam("/racerParam/throttleForwardMax",throttleMax);
   node.getParam("/racerParam/steerAngleMax",steerAngleMax);

   node.getParam("/joyParam/throttleAxis",throttleAxis);
   node.getParam("/joyParam/steerAxis",steerAxis);
   node.getParam("/joyParam/killSwitch",killSwitchButton);

   joyController = node.advertise<jetracer::jetRacerCar>("jetRacer_joyControl",100);
ROS_INFO("subscribe to joy");
   ros::Subscriber joyNode = node.subscribe<sensor_msgs::Joy>("joy",1000, joyCallback);   
   

  
   ros::spin();
}     



   
