#define enA 8       //OUTPUT PIN - to control motor A
#define in1 9
#define in2 10
#define phase_A 2   //INPUT PIN - encoder
#define phase_B 3

//----------

int pos = 0;     //when motor start, set that initial position = 0 = origin
int set_pos, error, energy;

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

  int d_err, i_err;
  static int prev_err;    //exist whole run-time
  long temp;
  
  d_err = err - prev_err;
  i_err += err;
  if (i_err > 100) i_err=100;
  if (i_err < -100) i_err=-100;

  prev_err = err;
  
  temp = kp*err + ki*i_err + kd*d_err;
  if (i_err > 255) i_err=255;
  if (i_err < -255) i_err=-255;
  
  return temp;
}

void loop() {
  Serial.println(pos);

  error = set_pos - pos;
  energy = pid(error, 1, 0, 0);
  rotate(energy);
}
