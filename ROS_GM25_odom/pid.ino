
// khong can khai bao lai in1, in2,.. va T, xung a, xung b
// 390.7 xung/vong

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
  tocdo_a = ((xung_a/ppr) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  tocdo_b = ((xung_b/ppr) / 0.01) * 60;  // xung/390/0.01 = vong/s x60 = vong/ph = RPM 
  
  xung_tb = (- xung_a + xung_b) / 2;
  vx = xung_tb*100*PI*d / 390;
  vtheta = (xung_tb - xung_b)*100*PI*d / (390*R);     // or (-xung_a - xung_tb)
  x+= (vx*0.01)*cos(theta);
  y+= (vx*0.01)*sin(theta);
  theta+= vtheta*0.01;
  
  xung_a = 0;
  E_a = Tocdodat_a - tocdo_a;
  Output_a = (alpha*E_a + beta*E1_a + gamma*E2_a + 2*T*LastOutput_a) / (2*T);
  LastOutput_a = Output_a;
  
  E2_a = E1_a;
  E1_a = E_a;
    
  xung_b = 0;
  E_b = Tocdodat_b - tocdo_b;
  Output_b = (alpha*E_b + beta*E1_b + gamma*E2_b + 2*T*LastOutput_b) / (2*T);
  LastOutput_b = Output_b;
  E2_b = E1_b;
  E1_b = E_b;
  
  rotate_a(Output_a);
  rotate_b(Output_b);
}
