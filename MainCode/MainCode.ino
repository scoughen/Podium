#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define USMIN  1000 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  1500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define servo0  0 // servo being driven
#define servo1  1 // servo being driven
#define servo2  2 // servo being driven
#define servo3  3 // servo being driven
#define servo4  4 // servo being driven
#define servo5  5 // servo being driven
#define servo6  6 // servo being driven
#define servo7  7 // servo being driven
#define servo8  8 // servo being driven
#define servo9  9 // servo being driven

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
  //------Servo setup
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

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
  for (int i = 0; i<=9; i++)
  {
    scale[i] = servo_control(i);
  }
  
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


//Servo Control Function
float servo_control(int servo){
  int ScaleVal = analogRead(potpin1);  //Reads value of potentiometer (value between 0 and 1023)
  val = map(ScaleVal,0,1023,0,90); //Converts 0-1023 range to 0-90
  if ((val >=0) && (val <18)){  
    pwm.writeMicroseconds(servo, 0*(USMAX-USMIN)/4+USMIN);    
  }
  if ((val >=18) && (val <36)){
    pwm.writeMicroseconds(servo, 1*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >=36) && (val <54)){
    pwm.writeMicroseconds(servo, 2*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >=54) && (val <72)){
    pwm.writeMicroseconds(servo, 3*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >=72) && (val <=90)){
    pwm.writeMicroseconds(servo, 4*(USMAX-USMIN)/4+USMIN);
  }
  return ScaleVal;  
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
