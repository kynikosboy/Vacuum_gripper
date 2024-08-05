#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def gripper_control():
    pub = rospy.Publisher('gripper_control', String, queue_size=10)
    rospy.init_node('gripper_control_node', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        command = input("Enter command (suction/hold/exhaust): ")
        rospy.loginfo(command)
        pub.publish(command)
        rate.sleep()

if __name__ == '__main__':
    try:
        gripper_control()
    except rospy.ROSInterruptException:
        pass

