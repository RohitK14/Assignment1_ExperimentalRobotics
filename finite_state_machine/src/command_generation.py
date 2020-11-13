#!/usr/bin/env python
"""
#   \file command_generation.py
#   \brief This file contains the command to call the robot for play behavior
#   \author Rohit Kumar
#   \version 0.2
#   \date 2020-11-13
#
"""
import rospy
import smach
import smach_ros
import time
import random
import numpy as np
from geometry_msgs.msg import Point
from std_msgs.msg import String
from std_msgs.msg import Bool

##
#   \brief the main function here published to rostopic.
#   The user publishes the command play to call the robot for playing


def main():
    # Node name command_generation
    rospy.init_node('command_genration')
    # Publishers and subscribers
    pub = rospy.Publisher('/command', String, queue_size=10)
    # frame rate
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        rospy.spin()
        txt = input("Write play to call the robot: ")
        if(txt == "Play" or txt == "play" or txt == "PLAY"):
            print("Valid command")
            txt = "play"
            pub.publish(txt)
        else:
            print('Invalid command')
            continue
        rate.sleep()


if __name__ == '__main__':
    main()
