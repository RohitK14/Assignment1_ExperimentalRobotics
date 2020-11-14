//Cpp
/**
 * @file random_motion.cpp
 * @author Rohit Kumar (rohitkb114@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

//ROS
/**
 * These are ROS specific headers 
 * 
 */
#include "ros/ros.h"
//Messages headers

#include <std_msgs/Int16.h>///< Integer related headers
#include <geometry_msgs/Point.h>///< Header required for geometry_messages
#include <std_msgs/Bool.h>

//Initialization for ros messages variables
geometry_msgs::Point move_coord;
std_msgs::Bool position_reached;
bool reached_= false;
//ros::Publisher pubMarker ;
//Subscriber callback for rosropic /moveToPose


/**
 * @brief posCallback function listens to the topic /moveToPos.
 * It records the postions to be reached.
 * The fucntion then declares that the positon is reached to be published on the topic /Rested
 * 
 * @param _point 
 * It takes the argument as point after subscribing to the topic /moveToPose
 */
void posCallback(geometry_msgs::Point _point)
{
    move_coord.x = _point.x ;
    move_coord.y = _point.y ;
    move_coord.z = _point.z ;
    reached_ =true;
    
}
/**
 * @brief 
 * In this funciton we listen subscribe to rostopic /moveToPose and publishes to rostopic 
 * /Reached.
 * The idea here is that we say the robot has reached the position only after the robot has
 * reahced the target.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char** argv)
{

    //ROS Initialization
    ros::init(argc, argv, "robot_motion");

    // Node handles
    ros::NodeHandle nh_glob;

    // Topics to which the node subscribes.

    // Topics to which the node publishes.
    ros::Subscriber sub= nh_glob.subscribe<geometry_msgs::Point>("/moveToPose",10,posCallback);
    ros::Publisher pubCommand = nh_glob.advertise<std_msgs::Bool>("/Reached",10);
    //Publish true to rostopic /Reached 
    if(reached_)
    {
        position_reached.data = true ;
        pubCommand.publish(position_reached);
        ROS_INFO("Postition reached.", move_coord);
    }
    else
    {
        position_reached.data = false;
        pubCommand.publish(position_reached);
    }
    

    //Frame rate
    ros::Rate rate(10);
    while (ros::ok()){

        ros::spinOnce();

        rate.sleep();
    }
    return 0;
}