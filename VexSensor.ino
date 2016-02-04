#define cutoff 700
int l, r, m;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  l = analogRead(2);
  m = analogRead(1);
  r = analogRead(0);
  //Serial.println(String(l) + ", " + String(m) + ", " + String(r));
  if (l > cutoff && !(m > cutoff) && !(r > cutoff)){
   Serial.println(F("Right")); 
  } else if (!(l > cutoff) && !(m > cutoff) && r > cutoff){
   Serial.println(F("Left"));
  } else if (m > cutoff){
   Serial.println(F("Middle"));
  } else if (l > cutoff && !(m > cutoff) && r > cutoff){
   Serial.println(F("Fork"));
  }
}
