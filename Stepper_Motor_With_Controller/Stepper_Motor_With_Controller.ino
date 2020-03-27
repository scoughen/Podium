#define StepsPerIncrement 20

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
    delay(4);
    digitalWrite(pulse, LOW);
    delay(4);
  }

  delay(1000);
}
