// PID: chỉ nên tăng/giảm các hệ số nhỏ nhất đến 0.01
// Tốc độ dao động cỡ +-10% (RPM)
// Kp = 10 bắt đầu có gai nhưng vẫn khá êm, 12 giật mạnh, 20 vọt lố hoàn toàn, 2 "biên" vận tốc ko song song
// Kp = 8 tốc độ hơi thấp so với set_vel, = 6 thì toàn gai đi xuống, =4 thì tầm 100 không gai
// Kp = 1 thì tầm 70 không gai, biên 20, bằng 5 tầm 110 êm biên 30, 
// Kp = 5 không có Ki thì ổn định ở 100, Kp = 6, Kd = 0.6 thì không êm lắm, lâu xác lập, Kp=6-9 nhiều gai
// Thêm Ki = 0.01 đã hơi mất ổn định (rè hơn. nhiều gai xuống) lên 0.1 thì sạn giật giât, 
// lên 0.6 thì như máy nghiền.
// Chốt Kp = 5, Ki = 0.6 , Kd = 0-> êm, tầm 120
// NHỚ: PID tính trên đầu ra chứ đừng tính trên cái trước đầu ra, vd tính trên RPM chứng không phải xung.
#include <TimerOne.h>   //avoid using PWM on pin 11, 12, 13

#define enA 7       //controls pin
#define in1 15
#define in2 14
#define phase_A 3   //encoder pins
#define phase_B 5

double T, xung;
double tocdo, Tocdodat;
double E, E1, E2;
double alpha, beta, gamma, Kp, Ki, Kd;
double Output, LastOutput;


void rotate(double energy) {
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

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);

  Tocdodat = 120; tocdo = 0;      //120 RPM (stable) - max ~200 RPM, below 5 RPM not run
  
  E = 0; E1 = 0; E2 = 0;
  Output = 0; LastOutput = 0;
  
  // Thong so PID
  T = 0.01;                       //thoi gian lay mau - s
  Kp = 5; Ki = 0.6; Kd = 0.0;  
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(phase_A), Demxung, FALLING);
  Timer1.initialize(10000);       // 10 ms
  Timer1.attachInterrupt(PID);
}

void loop() {
  int i;
  for (i=0; i<10; ++i)
    delay(i);
  Serial.println(tocdo);
}

void Demxung() {
  if (digitalRead(phase_B)==LOW)
    ++xung;
  else 
    --xung;
}

void PID() {
  tocdo = ((xung/390) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  xung = 0;
  E = Tocdodat - tocdo;
  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = -2*T*Kp + Ki*T*T - 4*Kd;
  gamma = 2*Kd;
  Output = (alpha*E + beta*E1 + gamma*E2 + 2*T*LastOutput) / (2*T);
  LastOutput = Output;
  E2 = E1;
  E1 = E;

  rotate(Output);
}
