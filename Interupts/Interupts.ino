const byte ledPin = 5;
const byte statPin = 13;
const byte interruptPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(statPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), FunnelSensor, CHANGE);
}

void loop() {
  digitalWrite(statPin, HIGH);
  delay(500);
  digitalWrite(statPin, LOW);
  delay(500);
}

void FunnelSensor() {
  digitalWrite(ledPin, digitalRead(interruptPin));
}
