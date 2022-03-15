#define enA 8       //OUTPUT PIN - to control motor A
#define in1 9
#define in2 10

#define phase_A 2   //INPUT PIN - encoder
#define phase_B 3

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(phase_A, INPUT);
  pinMode(phase_B, INPUT);

  digitalWrite(in1, HIGH);  //set rotate direction of motor A
  digitalWrite(in2, LOW);   
  analogWrite(enA, 126);    //set speed of motor A
  
  Serial.begin(9600);       //start Serial monitor

  int count = 0;
}

void loop() {
  Serial.print(digitalRead(phase_A), " ");   //see monitor and plotter for output of encoder

  prev = digitalRead(phase_A);
  if (digitalRead(phase_A)==1 && prev==0)
    ++count;
  Serial.println(count);
  //aaa
}
