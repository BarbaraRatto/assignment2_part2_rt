# How to run the code

To run the code the following things are needed:
- ROS2 foxy
- package robot_urdf

After cloning the needed packages in the workspace and after sourcing the right setup files, the workspace has to be compiled with colcon build.
Then to run the simulation you have to go in the workspace folder and run the following command:

	- ros2 launch robot_urdf gazebo.launch.py

Then to run the code developed in this package in another terminal run:

	- ros2 run assignment_2_part2 slalom


# What I have done

I have built a ROS package  called assignment_2_part2, that contains a node developed in ROS2 that with the use of a subscriber and a publisher controls the robot velocity based on the position.


## slalom.cpp

This node subscribes to the robot odometry topic of the robot and uses the information of its position in the callback function to build a velocity message that is sent by a publisher on the topic /cmd_vel to control the robot.
This velocity it's computed at each iteration to follow a slalom path described in the callback function.
