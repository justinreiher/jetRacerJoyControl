# jetRacerJoyControl
simple ROS node that makes use of joy to translate joystick inputs to car command messages

Tested with a logitech F310 gamepad

This ROS package requires the jetracer package found: https://github.com/justinreiher/jetRacerROSpkg

to send the translated joystick commands to the jetracer platform via the jetracer::jetRacerCar messages.

makes use of the sensor_msgs::Joy messages. The launch file ```joy_racer.launch``` by default tries to connect a joystick device with "/dev/input/js0" in the field:

```
<node respawn ="true" pkg ="joy"
		type = "joy_node" name ="joy">
		<param name ="dev" type = "string" value ="/dev/input/js0"/>
</node>
```
  
Modify the launch file for your own input.

The jetracer is configured to be running the ROS master node. In order to connect the joystick/gamepad to the jetracer in your bash terminal run the following commands:

```
export ROS_MASTER_URI=http://IP_ADDRESS_OF_JET_RACER:11311
export ROS_IP=IP_ADDRESS_OF_COMPUTER_CONNECTING_TO_JET_RACER
roslaunch joy_racer joy_racer.launch
```

Example:
```
export ROS_MASTER_URI=http://192.168.1.30:11311
export ROS_IP=192.168.1.31
roslaunch joy_racer joy_racer.launch
```
