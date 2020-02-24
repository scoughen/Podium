const byte interruptPin = 2;
int sel1flg = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(statPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), FunnelSensor, RISING);
}

void loop() {
  delay(1500); //Simulate 1 cycle
  if(sel1flg != 0) //if the beam was not tripped, the pellet did not exit the selector
  {
    //Problem between scale and selector exit!!!!
  }
  else //if the beam was tripped, the pellet exited the selector
  {
    sel1flg = 0; //reset selector flag
  }
}

void FunnelSensor() {
  sel1flg = 1; //set flag when pellet exits selector
}
