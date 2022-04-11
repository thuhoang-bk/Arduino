// Chỉnh để main() chạy trong 50-100ms thì plotter sẽ mượt, lấy gttb trong 100ms kq sẽ chính xác hơn
// Cấp nguồn motor trước/trong khi cấp nguồn Arduino, hoặc set vel mềm về 0 rồi set mềm lên 60.
// Chọn Kp theo tiêu chí: 1. lớn nhất để vel_ổn_định gần set_vel nhất có thể, sẽ có sai lệch tĩnh, 2. êm, ít gai, gai thấp
// Chọn Ki theo tiêu chí: Loại hoàn toàn sai lệch tĩnh, dao động tối thiểu, thời gian đáp ứng ngắn
//  Trong trường hợp này: Output bị giới hạn (255) nên Ki càng lớn sẽ càng đáp ứng nhanh, nhưng lớn quá tắt đi bật lại
    lâu về set_vel
// Vì Output bị giới hạn nên sẽ không có dao động, Ki không cần thiết trong trường hợp này.

// Kp: Tốc độ đáp ứng  | làm tăng dao động (1, 2, 3, .. 7, 8, 10 >> 7, 8 >> 7.5 >> 7.9)
// Ki: Loại sai lệch tĩnh (trong TH này: cả thời gian đáp ứng) | làm tăng dao động  (0.1, 1, 5, 10, 20 >> 15 >> 16)
// Kd: Giảm độ vọt lố (overshoot) | tăng độ ổn định (loại bỏ dao động) (0.1 >> 0.01 >> 0)

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

int count=0;
double sum_vel=0;

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

void Demxung() {
  if (digitalRead(phase_B)==LOW)
    ++xung;
  else 
    --xung;
}

void PID() {
  tocdo = ((xung/390) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  sum_vel += tocdo;
  xung = 0;
  E = Tocdodat - tocdo;
  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = -2*T*Kp + Ki*T*T - 4*Kd;
  gamma = 2*Kd;
  Output = (alpha*E + beta*E1 + gamma*E2 + 2*T*LastOutput) / (2*T);
  LastOutput = Output;
  E2 = E1;
  E1 = E;

  ++count;

  rotate(Output);
}
//---------------------

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);

  Tocdodat = 0; tocdo = 0;      //120-180 RPM (stable) - max ~200 RPM, below 5 RPM not run
  
  E = 0; E1 = 0; E2 = 0;
  Output = 0; LastOutput = 0;
  
  // Thong so PID
  T = 0.01;                       //thoi gian lay mau - s 5 0.6 0
  Kp = 7.9; Ki = 16; Kd = 0.0;  
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(phase_A), Demxung, FALLING);
  Timer1.initialize(10000);       // 10 ms
  Timer1.attachInterrupt(PID);
}

void loop() {
  if (count == 10) {
    Serial.println(double(sum_vel/count));
    count = 0;
    sum_vel = 0;
  }
}
