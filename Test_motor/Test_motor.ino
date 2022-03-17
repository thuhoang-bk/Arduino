#define enA 8       //OUTPUT PIN - to control motor A
#define in1 9
#define in2 10

#define phase_A 2   //INPUT PIN - encoder
#define phase_B 3

const int interrupt0 = 0;   // for pin 2, or digitalPinToInterrupt(2) see attachInterrupt
int pulse = 0;

void setup() {
  attachInterrupt (interrupt0, call_back, FALLING);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(phase_A, INPUT_PULLUP);
  pinMode(phase_B, INPUT_PULLUP);

  digitalWrite(in1, HIGH);  //set rotate direction of motor A
  digitalWrite(in2, LOW);   
  analogWrite(enA, 0);    //set speed of motor A
  
  Serial.begin(9600);       //start Serial monitor

}

void loop() {
  Serial.println(pulse);
}

void call_back() {
  if (digitalRead(phase_B) == LOW)
    ++pulse;
  else 
    --pulse;
}
