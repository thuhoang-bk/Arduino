#define enA 7       //OUTPUT PIN - to control motor A
#define in1 15
#define in2 14
#define in3 8
#define in4 9
#define enB 10       //OUTPUT PIN - to control motor B

#define phaseA_a 3   //INPUT PIN - encoder motor A
#define phaseB_a 5
#define phaseA_b 2   //INPUT PIN - encoder motor B
#define phaseB_b 4   

const int interrupt0 = 0;   // for pin 2, or digitalPinToInterrupt(2) see attachInterrupt
const int interrupt1 = 1;   // pin 3
int pulse_a = 0, pulse_b = 0;

void callback_a() {
  if (digitalRead(phaseB_a) == LOW)
    ++pulse_a;
  else 
    --pulse_a;
}

void callback_b() {
  if (digitalRead(phaseB_b) == LOW)
    ++pulse_b;
  else 
    --pulse_b;
}

void setup() {
  attachInterrupt (interrupt1, callback_a, FALLING);
  attachInterrupt (interrupt0, callback_b, FALLING);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(phaseA_a, INPUT_PULLUP);
  pinMode(phaseB_a, INPUT_PULLUP);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(phaseA_b, INPUT_PULLUP);
  pinMode(phaseB_b, INPUT_PULLUP);

//  digitalWrite(in1, HIGH);   // <1>LOW -> <2>HIGH la cung chieu duong encoder 
//  digitalWrite(in2, LOW);   
//  analogWrite(enA, 60);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);   
//  analogWrite(enB, 60);
  
  Serial.begin(9600);       // start Serial monitor

}


void loop() {
  Serial.print(pulse_a);
  Serial.print(", ");
  Serial.println(pulse_b);
}
