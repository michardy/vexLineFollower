#include <Servo.h>
#define cutoff 700
int l, r, m;

Servo servR;
Servo servL;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  servR.attach(3);
  servL.attach(5);
}

void loop() {
  l = analogRead(2);
  m = analogRead(1);
  r = analogRead(0);
  //Serial.println(String(l) + ", " + String(m) + ", " + String(r));
  if (l > cutoff && !(m > cutoff) && !(r > cutoff)){
   Serial.println(F("Right")); 
   servL.write(10);
   servR.write(90);
  } else if (!(l > cutoff) && !(m > cutoff) && r > cutoff){
   Serial.println(F("Left"));
   servR.write(10);
   servL.write(90);
  } else if (m > cutoff || (!(l > cutoff) && !(m > cutoff) && !(r > cutoff))){
   Serial.println(F("Middle"));
   servR.write(10);
   servL.write(10);
  } else if (l > cutoff && !(m > cutoff) && r > cutoff){
   Serial.println(F("Fork"));
   servL.write(10);
   servR.write(90);
  }
}
