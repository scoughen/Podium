#include <Servo.h>

Servo servo_1;  //Create servo object to control first servo
Servo servo_2;  //Create servo object to control second servo
Servo servo_3;  //Create servo object to control third servo
Servo servo_4;  //Create servo object to control fourth servo
Servo servo_5;  //Create servo object to control fith servo
Servo servo_6;  //Create servo object to control sixth servo
Servo servo_7;  //Create servo object to control seventh servo
Servo servo_8;  //Create servo object to control eighth servo
Servo servo_9;  //Create servo object to control nineth servo
Servo servo_10;  //Create servo object to control tenth servo

float scale[9];  //values for current readings from all scales

int pos = 0;  //Integer value for servo position

int potpin1 = 0;  //potentiometrer attached to analog pin zero
int potpin2 = 0;  //potentiometrer attached to analog pin zero
int potpin3 = 0;  //potentiometrer attached to analog pin zero
int potpin4 = 0;  //potentiometrer attached to analog pin zero
int potpin5 = 0;  //potentiometrer attached to analog pin zero
int potpin6 = 0;  //potentiometrer attached to analog pin zero
int potpin7 = 0;  //potentiometrer attached to analog pin zero
int potpin8 = 0;  //potentiometrer attached to analog pin zero
int potpin9 = 0;  //potentiometrer attached to analog pin zero
int potpin10 = 0;  //potentiometrer attached to analog pin zero
int val;  //variable to read value from the analogue pin

//--------Selector Interrupt Var's
const byte selectorInterruptPin = 2;
int sel1flg = 0;

//--------Funnel Interrupt Var's
const byte FunnelInterruptPin = 3;
int funnelState = 0;

//--------Cogwheel Error Checking Var's
const byte inlet0 = 15; //inlet sensor pin
const byte scale0 = A0; //scale pin
bool step0[9]; //1 element per line  -- value for pellet presence before cogwheel
bool step1[9]; //1 element per line  -- value for pellet presence when reached cogwheel
bool step2[9]; //1 element per line  -- value for pellet presence 1 cycle after reaching cogwheel
bool step3[9]; //1 element per line  -- value for pellet presence 2 cycles after reaching cogwheel
bool step4[9]; //1 element per line  -- value for pellet presence when reaches scale

//--------

void setup() {
  servo_1.attach(?);  //Servo 1 is attached to pin
  servo_2.attach(?);  //Servo 2 is attached to pin 
  servo_3.attach(?);  //Servo 3 is attached to pin
  servo_4.attach(?);  //Servo 4 is attached to pin
  servo_5.attach(?);  //Servo 5 is attached to pin
  servo_6.attach(?);  //Servo 6 is attached to pin
  servo_7.attach(?);  //Servo 7 is attached to pin
  servo_8.attach(?);  //Servo 8 is attached to pin
  servo_9.attach(?);  //Servo 9 is attached to pin
  servo_10.attach(?);  //Servo 10 is attached to pin

  //------Set up for Selector Interrupt
  pinMode(ledPin, OUTPUT);
  pinMode(statPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin), Selector, RISING);
  //------Set up for Funnel Interrupt
  pinMode(FunnelInterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FunnelInterruptPin), FunnelSensor, CHANGE);
  
  //------Set up for Cogwheel Error Checking
  pinMode(inlet0, INPUT);
  pinMode(scale0, INPUT);
  
  //------
}


void loop() {
  scale[0] = servo_control_1();
  scale[1] = servo_control_2();
  scale[2] = servo_control_3();
  scale[3] = servo_control_4();
  scale[4] = servo_control_5();
  scale[5] = servo_control_6();
  scale[6] = servo_control_7();
  scale[7] = servo_control_8();
  scale[8] = servo_control_9();
  scale[9] = servo_control_10();

  //-------Logic for Selector Interrupt
  if(sel1flg != 0) //if the beam was not tripped, the pellet did not exit the selector
  {
    //Problem between scale and selector exit!!!!
  }
  else //if the beam was tripped, the pellet exited the selector
  {
    sel1flg = 0; //reset selector flag
  }
  //------Logic for Funnel Interrupt
  
  if(funnelState == HIGH) //if the beam is still tripped, there is a jam in the funnel
  {
    //Clog at funnel!!!!
  }
  
  //------Logic for Cogwheel Error Checking
  step0[0] = digitalRead(inlet0);
  
  for (int i = 0; i<= 9; i++) //transfer pellet presence data down the line
  {
    step4[i] = step3[i];
    step3[i] = step2[i];
    step2[i] = step1[i];
    step1[i] = step0[i];
  }

  CogError(scale,step4)

  //------
}

//Servo 1 Function
float servo_control_1(){
  int val = analogRead(potpin1);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180); //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_1.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_1.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_1.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_1.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_1.write(162);
  }
return val;  

}
//Servo 2 Function
float servo_control_2(){
  int val = analogRead(potpin2);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_1.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_2.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_2.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_2.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_2.write(162);
  }
return val;
}

//Servo 3 Function
float servo_control_3(){
  int val = analogRead(potpin3);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_3.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_3.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_3.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_3.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_3.write(162);
  }
return val;
}

//servo 4 Function
float servo_control_3(){
  int val = analogRead(potpin4);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_3.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_3.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_3.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_3.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_3.write(162);
  }
return val;
}
  
//Servo 5 Function
float servo_control_5(){
  int val = analogRead(potpin5);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_5.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_5.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_5.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_5.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_5.write(162);
  }
return val;
}

//Servo 6 function
float servo_control_6(){
  int val = analogRead(potpin6);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_6.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_6.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_6.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_6.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_6.write(162);
  }
return val;
}

//Servo 7 Function
float servo_control_7(){
    int val = analogRead(potpin7);  //Reads value of potentiometer (value between 0 and 1023)
    val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
    if ((val >=0) && (val <36)){  
      servo_7.write(18);
      delay(15);     
    }
    if ((val >=36) && (val <72)){
       servo_7.write(54);
       delay(15);
    }
    if ((val >=72) && (val <108)){
      servo_7.write(90);
      delay(15);
    }
    if ((val >=108) && (val <144)){
      servo_7.write(126);
      delay(15);
    }
    if ((val >=144) && (val <=180)){
      servo_7.write(162);
    }
return val;
}

//Servo 7 Function
float servo_control_7(){
  int val = analogRead(potpin7);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_7.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_7.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_7.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_7.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_7.write(162);
  }

//Servo 8 Function
float servo_control_8(){
  int val = analogRead(potpin8);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_8.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_8.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_8.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_8.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_8.write(162);
  }
return val;
}

//Servo 9 Function
float servo_control_9(){
  int val = analogRead(potpin9);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_9.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_9.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_9.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_9.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_9.write(162);
  }
return val;
}

//Servo 10 Function
float servo_control_10(){
  int val = analogRead(potpin10);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(val,0,1023,0,180);  //Converts 0-1023 range to 0-180
  if ((val >=0) && (val <36)){  
    servo_10.write(18);
    delay(15);     
  }
  if ((val >=36) && (val <72)){
     servo_10.write(54);
     delay(15);
  }
  if ((val >=72) && (val <108)){
    servo_10.write(90);
    delay(15);
  }
  if ((val >=108) && (val <144)){
    servo_10.write(126);
    delay(15);
  }
  if ((val >=144) && (val <=180)){
    servo_10.write(162);
}
retun val;
  }

}

//------Cogwheel Error Check
void CogError(float scale[9],bool stepLast[9]) {
  for (int i = 1; i<=9; i++)
  {
      if(scale[i] != 0 && stepLast[i] == 1)
    {
      //no issues
    }
    else
    {
      //Issue between system inlet and scale!!!!
    }
  }
}

//------Selector ISR
void Selector() {
  sel1flg = 1; //set flag when pellet exits selector
}

//------Funnel ISR
void FunnelSensor() {
  funnelState = digitalRead(FunnelInterruptPin); //set or reset the flag
}
