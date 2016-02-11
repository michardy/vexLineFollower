#include <Servo.h>
#define cutoff 700
#define lowR 70
#define lowL 110
#define topR 0
#define topL 180

int l, r, m;

Servo servR;
Servo servL;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  servR.attach(10);
  servL.attach(11);
}

void loop() {
  l = analogRead(2);
  m = analogRead(1);
  r = analogRead(0);
  //Serial.println(String(l) + ", " + String(m) + ", " + String(r));
  if (l > cutoff && !(m > cutoff) && !(r > cutoff)){
   Serial.println(F("Right")); 
   servL.write(topL);
   servR.write(90);
  } else if (!(l > cutoff) && !(m > cutoff) && r > cutoff){
   Serial.println(F("Left"));
   servR.write(topR);
   servL.write(90);
  } else if (m > cutoff || (!(l > cutoff) && !(m > cutoff) && !(r > cutoff))){
   Serial.println(F("Middle"));
   servR.write(lowR);
   servL.write(lowL);
  } else if (l > cutoff && !(m > cutoff) && r > cutoff){
   Serial.println(F("Fork"));
   servL.write(topL);
   servR.write(90);
  }
}
