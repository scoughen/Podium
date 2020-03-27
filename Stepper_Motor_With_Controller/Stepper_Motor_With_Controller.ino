#define StepsPerIncrement 13

int pulse = 7;
int dir = 6;
int en = 5;

void setup() {
  pinMode (pulse, OUTPUT);
  pinMode (dir, OUTPUT);
  pinMode (en, OUTPUT);
}

void loop() {
  digitalWrite(dir, LOW);
  digitalWrite(en, HIGH);
  
  for (int i=0; i <= StepsPerIncrement; i++) {
    digitalWrite(pulse, HIGH);
    delay(50);
    digitalWrite(pulse, LOW);
    delay(50);
  }
}
