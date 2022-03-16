//----------USE TIMER TO COUNT ENCODER PULSES----------

#define enA 8       //OUTPUT PIN - to control motor A
#define in1 9
#define in2 10
#define phase_A 47   //INPUT PIN - encoder
#define phase_B 6


long time_prev = 0;
int vel;
float set_vel_rpm = 180; // (RPM) max 180 RPM = 1180 pulses/s = 3 vong/s
float set_vel = set_vel_rpm*390.0/60.0 / 100; // convert to pulse per 10 millisec
float error;
int energy;

void rotate(int energy) {
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

  //kích hoạt bộ đếm của Timer1, reset thanh ghi đếm xung
  TCNT5=0x00;           //thanh ghi đếm xung của Timer 1
  TCCR5A=0x00;          //Tắt hết các chức năng của Timer 1
  TCCR5B=0x07;          //Đếm xung sườn xuống (encoder) 0x06=0b110 sườn lên
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);
  
  Serial.begin(9600);  
}


int pid(float err, float kp, float ki, float kd) {

  static float prev_err = set_vel;
  float d_err, i_err;
  int temp;
  
  d_err = err - prev_err;
  i_err += err;

  prev_err = err;
  
  temp = int(kp*err + ki*i_err + kd*d_err);
  if (temp > 255) temp=255;
  if (temp < -255) temp=-255;
  
  return temp;
}

void loop() {
  
  if (millis()-time_prev >=10) {    //max output: 1180 pulse/sec = 3 rps = 180 rpm
    time_prev = millis();
    vel = TCNT5;
    TCNT5=0;

    error = set_vel - vel;
    energy = pid(error, 80, 80, 0);
    rotate(energy);                  

    Serial.print(set_vel);
    Serial.print(" ");
    Serial.println(vel);  //*6000.0/390.0);  //conver back to RPM     
  }
  
}
