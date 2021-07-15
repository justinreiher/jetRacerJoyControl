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
int resume;
bool stop;

void joyCallback(const sensor_msgs::Joy::ConstPtr& joyMsg)
{
    float throttle;
    float steerAngle;

     jetracer::jetRacerCar carMsg;

     carMsg.throttle = 0;
     carMsg.steerAngle = 0;
    
    if(!stop){
    	throttle   = throttleMax*joyMsg->axes[throttleAxis];
    	steerAngle = steerAngleMax*joyMsg->axes[steerAxis];
	carMsg.throttle = throttle;
        carMsg.steerAngle = steerAngle;
    }

     
     if(joyMsg->buttons[killSwitchButton] && !stop){
        ROS_INFO("e-stop pressed");
        stop = true;
	carMsg.throttle = 0;
        carMsg.steerAngle =0;
     }

     if(joyMsg->buttons[resume]){
        ROS_INFO("Continue Operation Button Pressed");
	stop = false;
     }

     joyController.publish(carMsg);
}


int main(int argc, char** argv)
{

   stop = false;

   ros::init(argc,argv,"jetRacer_joy");
   ros::NodeHandle node;


   ros::Subscriber joyNode = node.subscribe<sensor_msgs::Joy>("joy",100, joyCallback);   
   joyController = node.advertise<jetracer::jetRacerCar>("/jetRacer_Controller",100);

   node.getParam("/racerParam/throttleForwardMax",throttleMax);
   node.getParam("/racerParam/steerAngleMax",steerAngleMax);

   node.getParam("/joyParam/throttleAxis",throttleAxis);
   node.getParam("/joyParam/steerAxis",steerAxis);
   node.getParam("/joyParam/killSwitchButton",killSwitchButton);
   node.getParam("/joyParam/resumeSwitch",resume);

  
   ros::spin();
}     



   
