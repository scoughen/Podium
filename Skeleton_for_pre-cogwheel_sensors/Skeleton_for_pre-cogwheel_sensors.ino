const byte inlet0 = 15; //inlet sensor pin
const byte scale0 = A0; //scale pin
bool step0[9]; //1 element per line  -- value for pellet presence before cogwheel
bool step1[9]; //1 element per line  -- value for pellet presence when reached cogwheel
bool step2[9]; //1 element per line  -- value for pellet presence 1 cycle after reaching cogwheel
bool step3[9]; //1 element per line  -- value for pellet presence 2 cycles after reaching cogwheel
bool step4[9]; //1 element per line  -- value for pellet presence when reaches scale
float read0; //current scale reading

void setup() {
  pinMode(inlet0, INPUT);
  pinMode(scale0, INPUT);
}

void loop() {
  step0[0] = digitalRead(inlet0);
  read0 = analogRead(scale0);
  
  for (int i = 0, i<= 9, i++)
  {
    step4[i] = step3[i];
    step3[i] = step2[i];
    step2[i] = step1[i];
    step1[i] = step0[i];
  }

  if(read0 != 0 && step4[0] == 1)
  {
    //no issues
  }
  else
  {
    //PROBLEM!!!!!!!
  }
}
