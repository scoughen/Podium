const byte interruptPin = 2;
int funnelState = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), FunnelSensor, CHANGE);
}

void loop() {
  delay(1500); //simulate 1 cycle
  if(funnelState == HIGH) //if the beam is still tripped, there is a jam in the funnel
  {
    //Clog at funnel!!!!
  }
}

void FunnelSensor() {
  funnelState = digitalRead(interruptPin); //set or reset the flag
}
