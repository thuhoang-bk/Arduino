/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
int i=0;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  ++i;
  if (i>1000) i=0;
  str_msg.data = itoa(i, hello, 10);
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1);
}
