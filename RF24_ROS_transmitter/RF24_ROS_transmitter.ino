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
double R = 0.139, d = 0.063; //m, 1/2 wheel distance and wheel diameter. Dtb=28.6, Dt=27.7. middle

void presskey_callback(const geometry_msgs::Twist& vel_msg){
  linear_x = vel_msg.linear.x * 60/(PI*d);        // m/s -> RPM
  angular_z = vel_msg.angular.z*R * 60/(PI*d);    // rad/s -> RPM
  
  Tocdodat[0] = -linear_x - angular_z;
  Tocdodat[1] =  linear_x - angular_z;

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
