#include <Servo.h>
#include <EEPROM.h>
#define btnPin 5
#define cutoff 200
#define lowR 70
#define lowL 125//110
#define topR 0
#define topL 180

int l, r, m;

bool mode = false;
int iter = 0;

Servo servR;
Servo servL;

void setup() {
  Serial.begin(9600);//start serial logging
  Serial.println(F("start"));
  pinMode(btnPin,INPUT);//sets up button
  if (analogRead(btnPin) < 80){
    Serial.println(F("button pressed"));
    mode = true;
    for (int i=0; i<1000; i+=3){
      Serial.println(String(EEPROM.read(i))+", "+String(EEPROM.read(i+1))+", "+String(EEPROM.read(i+2)));
    }
  } else {
    for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
    }
  }
  Serial.println(F("read"));
  pinMode(3, OUTPUT);
  servR.attach(10);
  servL.attach(11);
  bool test = true;
  int high = 516;
  int low = 516;
  for (int i; i<100; i++){
    l = analogRead(2);
    m = analogRead(1);
    r = analogRead(0);
    if (l > high){
      high = l;
    }
    if (l < low){
      low = l;
    }
    if (m > high){
      high = m;
    }
    if (m < low){
      low = m;
    }
    if (r > high){
      high = r;
    }
    if (r < low){
      low = r;
    }
    delay(1);
  }
}

void loop() {
  if (!(mode)){
    l = analogRead(2);
    EEPROM.write(iter, l);
    iter++;
    m = analogRead(1);
    EEPROM.write(iter, m);
    iter++;
    r = analogRead(0);
    EEPROM.write(iter, r);
    iter++;
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
      servL.write(lowL);
      servR.write(lowR);
    }
  }
}
