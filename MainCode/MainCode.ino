#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

//------User Controlled Values
  //Weight Thresholds
    #define VeryLow 0.500 // (g)
    #define Low 0.525 // (g)
    #define High 0.535 // (g)
    #define VeryHigh 0.550 // (g)
//------END OF USER CONTROLLED VALUES

#define scaleTime 1100  //time spent weighing each pellet in miliseconds

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define USMIN  1000 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  1500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

float scale[9];  //values for current readings from all scales

//--------Stepper Motor Var's
#define StepsPerIncrement 24
int pulse = 7; //pulse pin
int dir = 6; // direction pin
int en = 5; // enable pin

//--------Scale Calibration Var's
float ReadingA_Strain[9];
float LoadA_Strain[9]; 
float ReadingB_Strain[9];
float LoadB_Strain[9];

//--------Selector Interrupt Var's
const byte SelectorInterruptPin = 2;
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
  //--------Scale Calibration Data
    //--------Scale 0
      ReadingA_Strain[0] = 755.0;
      LoadA_Strain[0] = 0.0; //  (g) 
      ReadingB_Strain[0] = 781.0;
      LoadB_Strain[0] = 2.9; //  (g) 
    //--------Scale 1
      ReadingA_Strain[1] = 866.0;
      LoadA_Strain[1] = 0.0; //  (g) 
      ReadingB_Strain[1] = 947.0;
      LoadB_Strain[1] = 2.9; //  (g) 
    //--------Scale etc.......................................

  //------Servo setup
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  //------Set up for Stepper Motor
  pinMode (pulse, OUTPUT);
  pinMode (dir, OUTPUT);
  pinMode (en, OUTPUT);

  //------Set up for Reading Scales
  analogReference(INTERNAL1V1);

  //------Set up for Selector Interrupt
  pinMode(SelectorInterruptPin, INPUT_PULLUP);
  int sel1flg;
  
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin), Selector, RISING);
  //------Set up for Funnel Interrupt
  pinMode(FunnelInterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FunnelInterruptPin), FunnelSensor, CHANGE);
  
  //------Set up for Cogwheel Error Checking
  pinMode(inlet0, INPUT);
  pinMode(scale0, INPUT);
}


void loop() {
  for (int i = 0; i<=0; i++)
  {
    scale[i] = servo_control(i);
  }

  //-------Cogwheel Control
  digitalWrite(dir, LOW);
  digitalWrite(en, HIGH);
  
  for (int i=0; i <= StepsPerIncrement; i++) {
    digitalWrite(pulse, HIGH);
    delay(10);
    digitalWrite(pulse, LOW);
    delay(10);
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

  CogError(scale,step4);

  //------
}//End of Main Loop


//------Servo Control Function
float servo_control(int servo){
  float val = ScaleRead(servo);  //Reads value of scale
  if ((val < VeryLow)){  
    pwm.writeMicroseconds(servo, 0*(USMAX-USMIN)/4+USMIN);    
  }
  if ((val >= VeryLow) && (val < Low)){
    pwm.writeMicroseconds(servo, 1*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >= Low) && (val < High)){
    pwm.writeMicroseconds(servo, 2*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >= High) && (val < VeryHigh)){
    pwm.writeMicroseconds(servo, 3*(USMAX-USMIN)/4+USMIN);
  }
  if ((val >= VeryHigh)){
    pwm.writeMicroseconds(servo, 4*(USMAX-USMIN)/4+USMIN);
  }
  return val;  
}

//------Load Cell Reading Function
float ScaleRead(int scale) {
  float ScaleVal = 0;
  float sum = 0;
  
  for (int i = 0; i<=scaleTime; i++) {
    ScaleVal = analogRead(scale);  // analog in 0 for Strain 1
    sum = sum + ScaleVal;
    delay(1);
  }

  ScaleVal = sum/scaleTime;
  Serial.print(ScaleVal);
  Serial.print("\t");
  
  float weight = ((LoadB_Strain[scale] - LoadA_Strain[scale])/(ReadingB_Strain[scale] - ReadingA_Strain[scale])) * (ScaleVal - ReadingA_Strain[scale]) + LoadA_Strain[scale];

  Serial.print(weight);
  Serial.print("\n");
  return weight;
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
