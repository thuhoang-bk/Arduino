//  - Để đầu ra RPM thì kết quả hiển thị phải đo GTTB thì mới đánh giá được,
//  chứ để nhấp nhô thì thấy nó nhảy quanh 60 chứ biết đúng là bao nhiêu
//  
//  - Để gttb tính trên 100 chu kì (1s) nhìn khá ổn, 10s hơi lâu, 100ms >?
//  >> thử 100ms: nhìn mượt và nhanh hơn, mỗi vòng main tầm 100ms là đẹp
//    (thực ra for i=1 -> 10 delay() chính là 50ms rồi)
//    
//  - Nguồn tổ ong 11.3V để hiệu chỉnh PID nên khi dùng pin đáp ứng tốt nhất sẽ
//  đạt trong khoảng điện áp gần 11.3V
//  
//  - count = 10, bắt đầu chỉnh Kp, Ki, Kd
#include <TimerOne.h>   //avoid using PWM on pin 11, 12, 13

#define enA 7      //controls pin
#define in1 15
#define in2 14
#define phaseA_a 3   //encoder pins
#define phaseB_a 5

#define in3 8
#define in4 9
#define enB 10      //controls pin
#define phaseA_b 2   //encoder pins
#define phaseB_b 4

double T, xung_a, xung_b;
double tocdo_a, tocdo_b, Tocdodat_a, Tocdodat_b;
double E_a, E1_a, E2_a, E_b, E1_b, E2_b;
double alpha, beta, gamma, Kp, Ki, Kd;
double Output_a, LastOutput_a, Output_b, LastOutput_b;

int count=0;
long sum_vel_a=0, sum_vel_b=0;
double avg_vel_a=0, avg_vel_b=0;

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
  sum_vel_a += tocdo_a;
  xung_a = 0;
  E_a = Tocdodat_a - tocdo_a;
  Output_a = (alpha*E_a + beta*E1_a + gamma*E2_a + 2*T*LastOutput_a) / (2*T);
  LastOutput_a = Output_a;
  E2_a = E1_a;
  E1_a = E_a;
    
  tocdo_b = ((xung_b/390) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  sum_vel_b += tocdo_b;
  xung_b = 0;
  E_b = Tocdodat_b - tocdo_b;
  Output_b = (alpha*E_b + beta*E1_b + gamma*E2_b + 2*T*LastOutput_b) / (2*T);
  LastOutput_b = Output_b;
  E2_b = E1_b;
  E1_b = E_b;

  ++count;
  
  rotate_a(Output_a);
  rotate_b(Output_b);
}
//--------------------------


void setup() {
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
  
  Tocdodat_a = 60; tocdo_a = 0;      //120 RPM (stable) - max ~200 RPM, below 5 RPM not run
  Tocdodat_b = 60; tocdo_b = 0;
  
  E_a = 0; E1_a = 0; E2_a = 0;
  Output_a = 0; LastOutput_a = 0;
  E_b = 0; E1_b = 0; E2_b = 0;
  Output_b = 0; LastOutput_b = 0;
  
  // Thong so PID
  T = 0.01;                       //thoi gian lay mau - s
  Kp = 7.9; Ki = 16.0; Kd = 0.0;  

  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = -2*T*Kp + Ki*T*T - 4*Kd;
  gamma = 2*Kd;

  Serial.begin(9600);
  Serial.println("avg_vel_a avg_vel_b");
  attachInterrupt(digitalPinToInterrupt(phaseA_a), Demxung_a, FALLING);
  attachInterrupt(digitalPinToInterrupt(phaseA_b), Demxung_b, FALLING);
  Timer1.initialize(10000);       // 10 ms
  Timer1.attachInterrupt(PID);    // PID check speed and control speed of 2 motors periodically
}

void loop() {
  if (count == 10) {
    Serial.print(double(sum_vel_a/count));
    Serial.print(", ");
    Serial.println(double(sum_vel_b/count));
    count = 0;
    sum_vel_a = 0;
    sum_vel_b = 0; 
  }
}
