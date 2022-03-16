#define enA 8       //OUTPUT PIN - to control motor A
#define in1 9
#define in2 10
#define phase_A 2   //INPUT PIN - encoder
#define phase_B 3

//----------

int pos = 0;     //when motor start, set that initial position = 0 = origin
int set_pos = 100, error, energy;

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


void callback() {
  if (digitalRead(phase_B) == LOW)
    ++pos;
  else 
    --pos;
}
void setup() {
  attachInterrupt (0, callback, FALLING); //(pin_intrpt_happen, callback, FALLING/RISING)

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);
  
  Serial.begin(9600);       //start Serial monitor
}


int pid(int err, int kp, int ki, int kd) {

  static int prev_err = set_pos;    //exist whole run-time but init once, value update each call to pid()
  int d_err, i_err;
  long temp;
  
  d_err = err - prev_err;
  i_err += err;

  prev_err = err;
  
  temp = kp*err + ki*i_err + kd*d_err;
  if (temp > 255) temp=255;
  if (temp < -255) temp=-255;
  
  return temp;
}

void loop() {
  Serial.println(pos);

  error = set_pos - pos;

  energy = pid(error, 10, 30, 200);   
  //range 0-390: 10 30 200  != (1, 3, 20) --general: (k, 0, 0) but osci and sse.
  //range 0-2000: 10, 6, 120
  //range 0-5000: 1, 3, 100 etc.   >>infinite pos, but finite speed
  rotate(energy); 

  //PID help "lock" position while if..else just restore position when use force to rotate motor.
}
