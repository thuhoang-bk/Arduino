// Kp=19 >1 page, 18.1 1/2page, 18 ? 17.5 1/5p test x5, Kd 0.6
// chọn để ko còn gai, Kd=2 bắt đầu rung mất ổn định, Ki=10, nếu không có Ki thì không
// bị vọt lố nhưng cũng không quay được chính xác đến, ví dụ 360 mà sẽ là 359. nếu lớn quá 180
// sẽ vọt trên 200, 360 lên 440 (nếu để Ki=20). Ki nhỏ 0.1-5 thì sai số xác lập lớn, tg đáp ứng lâu.

//Bộ PID kiểu cũ thì đáp ứng nhanh, chính xác không vọt nhưng với vị trí đặt lớn thì hoạt động sai.

#include <TimerOne.h>

#define enA 8       //controls pin
#define in1 9
#define in2 10
#define phase_A 2   //encoder pins
#define phase_B 3

double T, xung;
double vitri, Vitridat;
double E, E1, E2;
double alpha, beta, gamma, Kp, Ki, Kd;
double Output, LastOutput;


void rotate(double energy) {
  if (energy > 255) energy=255;
  if (energy < -255) energy=-255;
  if (energy > 0) {
    digitalWrite(in1, HIGH);      //set rotate direction of motor A
    digitalWrite(in2, LOW);   
    analogWrite(enA, energy);     //set speed of motor A
  }
  else {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);   
    analogWrite(enA, -energy);  
  }
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);

  Vitridat = 180; vitri = 0;
  E = 0; E1 = 0; E2 = 0;
  Output = 0; LastOutput = 0;
  // Thong so PID
  T = 0.01;                       //thoi gian lay mau
  Kp = 17.5; Ki = 10; Kd = 0.6;  

  Serial.begin(9600);
  attachInterrupt(0, Demxung, FALLING);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(PID);
}

void loop() {
  int i;
  for (i=0; i<10; ++i)
    delay(i);
  Serial.println(vitri);
}

void Demxung() {
  if (digitalRead(phase_B)==LOW)
    ++xung;
  else 
    --xung;
}

void PID() {
  vitri = xung*360 / 390;    //tong cong 1000xung -> 1000/390 vong x 60 -> deg
  E = Vitridat - vitri;
  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = -2*T*Kp + T*T*Ki - 4*Kd;
  gamma = 2*Kd;
  Output = (alpha*E + beta*E1 + gamma*E2 + 2*T*LastOutput) / (2*T);
  LastOutput = Output;
  E2 = E1;
  E1 = E;

  rotate(Output);
}
