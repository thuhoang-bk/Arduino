#include <TimerOne.h>   //avoid using PWM on pin 11, 12, 13
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>

#define enA 7      //speed control pin
#define in1 15
#define in2 14
#define phaseA_a 3   //encoder pins
#define phaseB_a 5

#define in3 8
#define in4 9
#define enB 10      //speed control pin
#define phaseA_b 2   //encoder pins
#define phaseB_b 4

ros::NodeHandle  nh;
ros::Time current_time, last_time;

double T, xung_a, xung_b;
double tocdo_a, tocdo_b, Tocdodat_a, Tocdodat_b;
double E_a, E1_a, E2_a, E_b, E1_b, E2_b;
double alpha, beta, gamma, Kp, Ki, Kd;
double Output_a, LastOutput_a, Output_b, LastOutput_b;
double linear_x = 0, angular_z = 0;

double x=0.0, y=0.0, th=0.0;
double vx=0.0, vth=0.0;
double d=6.3; //diameter of wheel in cm

void rotate_a(double energy) {
  if (energy > 255) energy=255;
  if (energy < -255) energy=-255;
  if (energy > 0) {
    digitalWrite(in1, LOW);      //set rotate direction of motor A
    digitalWrite(in2, HIGH);   
    analogWrite(enA, energy);     //set speed of motor A
  }
  else {
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);   
    analogWrite(enA, -energy);  
  }
}

void rotate_b(double energy) {
  if (energy > 255) energy=255;
  if (energy < -255) energy=-255;
  if (energy > 0) {
    digitalWrite(in3, LOW);      //set rotate direction of motor A
    digitalWrite(in4, HIGH);   
    analogWrite(enB, energy);     //set speed of motor A
  }
  else {
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW);   
    analogWrite(enB, -energy);  
  }
}

void presskey_callback(const geometry_msgs::Twist& vel_msg){
  linear_x = vel_msg.linear.x;                    //RPM
  angular_z = vel_msg.angular.z;                  //rad/s
  
  Tocdodat_a = -linear_x - angular_z * 30/PI;     //RPM
  Tocdodat_b =  linear_x - angular_z * 30/PI;
  
  vx  = linear_x*PI*d / 60;                       //cm/s
  vth = angular_z;                                //rad/s
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &presskey_callback);
nav_msgs::Odometry odom_msg;
ros::Publisher odom_pub("odom", &odom_msg);
tf::TransformBroadcaster odom_broadcaster;

void setup()
{ 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phaseA_a, INPUT_PULLUP);
  pinMode(phaseB_a, INPUT_PULLUP);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(phaseA_b, INPUT_PULLUP);
  pinMode(phaseB_b, INPUT_PULLUP);
  Tocdodat_a = 0; tocdo_a = 0;      //120 RPM (stable) - max ~200 RPM, below 5 RPM not run
  Tocdodat_b = 0; tocdo_b = 0;
  
  E_a = 0; E1_a = 0; E2_a = 0;
  Output_a = 0; LastOutput_a = 0;
  E_b = 0; E1_b = 0; E2_b = 0;
  Output_b = 0; LastOutput_b = 0;
  
  // Thong so PID
  T = 0.01;                       //thoi gian lay mau - s
  Kp = 5; Ki = 0.6; Kd = 0.0;  

  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = -2*T*Kp + Ki*T*T - 4*Kd;
  gamma = 2*Kd;

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(phaseA_a), Demxung_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(phaseA_b), Demxung_b, FALLING);
  Timer1.initialize(10000);       // 10 ms
  Timer1.attachInterrupt(PID);    // PID check speed and control speed of 2 motors periodically
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(odom_pub);
  
  last_time = nh.now();
}

void Demxung_a() {
  if (digitalRead(phaseB_a)==LOW)
    ++xung_a;
  else 
    --xung_a;
}

void Demxung_b() {
  if (digitalRead(phaseB_b)==LOW)
    ++xung_b;
  else 
    --xung_b;
}

void PID() {
  tocdo_a = ((xung_a/390) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  xung_a = 0;
  E_a = Tocdodat_a - tocdo_a;
  Output_a = (alpha*E_a + beta*E1_a + gamma*E2_a + 2*T*LastOutput_a) / (2*T);
  LastOutput_a = Output_a;
  
  E2_a = E1_a;
  E1_a = E_a;
    
  tocdo_b = ((xung_b/390) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  xung_b = 0;
  E_b = Tocdodat_b - tocdo_b;
  Output_b = (alpha*E_b + beta*E1_b + gamma*E2_b + 2*T*LastOutput_b) / (2*T);
  LastOutput_b = Output_b;
  E2_b = E1_b;
  E1_b = E_b;

  rotate_a(Output_a);
  rotate_b(Output_b);
}

void loop()                 //you should set speed=30, turn=2, peace. linear=RPM, angular=rad/s
{ 
  nh.spinOnce();            //check for incoming cmd_vel
  current_time = nh.now();
  
  //compute odometry in a typical way given the velocities of the robot
  double dt = current_time.toSec() - last_time.toSec();
  double delta_x = vx * cos(th) * dt;
  double delta_y = vx * sin(th) * dt;
  double delta_th = vth * dt;
  x += delta_x;
  y += delta_y;
  th += delta_th;
  
  //since all odometry is 6DOF we'll need a quaternion created from yaw
  geometry_msgs::Quaternion odom_quat = tf::createQuaternionFromYaw(th);

  //-------first, we'll publish the transform over tf
  geometry_msgs::TransformStamped odom_trans;
  odom_trans.header.stamp = current_time;
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";

  odom_trans.transform.translation.x = x;
  odom_trans.transform.translation.y = y;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = odom_quat;

  //send the transform
  odom_broadcaster.sendTransform(odom_trans);

  //-------next, we'll publish the odometry message over ROS
  nav_msgs::Odometry odom;
  odom.header.stamp = current_time;
  odom.header.frame_id = "odom";

  //set the position
  odom.pose.pose.position.x = x;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation = odom_quat;

  //set the velocity
  odom.child_frame_id = "base_link";
  odom.twist.twist.linear.x = vx;
  odom.twist.twist.angular.z = vth;

  //publish the message
  //odom_pub.publish(&odom);

  last_time = current_time;
  delay(1000);  // velocity change should take effect after 1 sec
}
