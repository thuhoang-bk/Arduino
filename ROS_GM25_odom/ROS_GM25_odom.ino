#include <TimerOne.h>   //avoid using PWM on pin 11, 12, 13
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

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

double T, xung_a, xung_b, xung_tb;
double tocdo_a, tocdo_b, Tocdodat_a, Tocdodat_b;
double E_a, E1_a, E2_a, E_b, E1_b, E2_b;
double alpha, beta, gamma, Kp, Ki, Kd;
double Output_a, LastOutput_a, Output_b, LastOutput_b;
double linear_x = 0, angular_z = 0;
double R = 14.3, d = 6.3; //cm, 1/2 wheel distance and wheel diameter.
double vx=0, vtheta=0, x=0, y=0, theta=0;

ros::NodeHandle  nh;

geometry_msgs::Twist state_msg;

void presskey_callback(const geometry_msgs::Twist& vel_msg){
  linear_x = vel_msg.linear.x * 60/(PI*d);      //cm/s -> RPM
  angular_z = vel_msg.angular.z*R * 60/(PI*d);    //rad/s -> RPM
  
  Tocdodat_a = -linear_x - angular_z;
  Tocdodat_b =  linear_x - angular_z;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &presskey_callback );
ros::Publisher pub("robot_state", &state_msg);

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

  //Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(phaseA_a), Demxung_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(phaseA_b), Demxung_b, FALLING);
  Timer1.initialize(10000);       // 10 ms
  Timer1.attachInterrupt(PID);    // PID check speed and control speed of 2 motors periodically
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}


void loop()                 //you should set speed=30, turn=2, peace. linear=RPM, angular=rad/s
{ 

  state_msg.linear.x = x;
  state_msg.linear.y = y; 
  state_msg.linear.z = theta;
  state_msg.angular.x = vx;
  state_msg.angular.y = vtheta;
  
  pub.publish(&state_msg);
  
  nh.spinOnce();
  delay(10);                //delay(1) will loss sync - unable sub topic aka. rostopic echo nothing.
}
