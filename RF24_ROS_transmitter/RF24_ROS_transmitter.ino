#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

RF24 radio(9, 10); // CE, CSN
ros::NodeHandle  nh;
const byte address[6] = "00001";
double Tocdodat[2];
double linear_x = 0, angular_z = 0;


void presskey_callback(const geometry_msgs::Twist& vel_msg){
  linear_x = vel_msg.linear.x;
  angular_z = vel_msg.angular.z;
  
  Tocdodat[0] = -linear_x - angular_z * 30/PI; //linear_x: RPM, Tocdodat: RPM
  Tocdodat[1] =  linear_x - angular_z * 30/PI;

  radio.write(&Tocdodat, sizeof(Tocdodat));
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &presskey_callback );

void setup()
{ 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);  //công suất DBm (W), tùy khoảng cách, mức cao cần dùng tụ
  radio.stopListening();
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop()                 //you should set speed=30, turn=2, peace. linear=RPM, angular=rad/s
{ 
  nh.spinOnce();
  delay(1);
}
