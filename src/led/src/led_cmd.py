#!/usr/bin/python

import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Joy

#create publisher

color_pub = rospy.Publisher('color_cmd', Float32MultiArray, queue_size = 1)


def joy_cb(msg):

	a = Float32MultiArray(data = [msg.axes[1], msg.axes[0], msg.buttons[0] ]) 

	color_pub.publish( a )

def led_command():
	print 'LED Command Initialized...'
	rospy.init_node('led_cmd', anonymous=True)
	rospy.Subscriber("/joy", Joy,  joy_cb)
	rospy.spin()



if __name__ == '__main__':
	led_command()


