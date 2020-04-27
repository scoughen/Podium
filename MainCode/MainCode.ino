#include <Adafruit_PWMServoDriver.h>
#include <Ard2499.h>
#include <Wire.h>

//------User Controlled Values
  //Weight Thresholds
    #define VeryLow 0.500 // (g)
    #define Low 0.525 // (g)
    #define High 0.535 // (g)
    #define VeryHigh 0.550 // (g)
    #define binMax 100000 // maximum number of pellets that can enter a bin before stoping the process
//------END OF USER CONTROLLED VALUES (Calibration values start at line 92)

#define scaleTime 1  //time spent weighing each pellet in miliseconds

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Ard2499 adc;

//--------Servo Settings
#define USMIN  1000 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  1500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

float scale[10];  //values for current readings from all scales

//--------Stepper Motor Var's
#define StepsPerIncrement 10*4 //   <-- assumes microstepping with 4 microsteps per whole step
int pulse = 7; //pulse pin
int dir = 6; // direction pin
int en = 5; // enable pin

//--------Scale Calibration Var's
float ReadingA_Strain[10];
float LoadA_Strain[10]; 
float ReadingB_Strain[10];
float LoadB_Strain[10];

//--------Bin Contents Var's
int VeryLowCount = 0;
int LowCount = 0;
int GoodCount = 0;
int HighCount = 0;
int VeryHighCount = 0;

//--------Selector Interrupt Var's
const byte SelectorInterruptPin0 = 2;
const byte SelectorInterruptPin1 = 3;
const byte SelectorInterruptPin2 = 18;
const byte SelectorInterruptPin3 = 19;
const byte SelectorInterruptPin4 = 20;
const byte SelectorInterruptPin5 = 21;
//This allows for 6 channels to have the selector throughput monitored
//If monitoring the rest of the channels is desired, pin change interrupts will be needed
int sel1flg[6] = {0,0,0,0,0,0};

//--------Cogwheel Error Checking Var's
const byte inlet0 = 8; //inlet sensor pin
const byte inlet1 = 9; //inlet sensor pin
const byte inlet2 = 10; //inlet sensor pin
const byte inlet3 = 11; //inlet sensor pin
const byte inlet4 = 12; //inlet sensor pin
const byte inlet5 = 13; //inlet sensor pin          <--  need to finalize ports
const byte inlet6 = 14; //inlet sensor pin
const byte inlet7 = 15; //inlet sensor pin
const byte inlet8 = 16; //inlet sensor pin
const byte inlet9 = 17; //inlet sensor pin
const byte scale0 = A0; //scale pin
bool step0[10]; //1 element per line  -- value for pellet presence before cogwheel
bool step1[10]; //1 element per line  -- value for pellet presence when reached cogwheel
bool step2[10]; //1 element per line  -- value for pellet presence 1 cycle after reaching cogwheel
bool step3[10]; //1 element per line  -- value for pellet presence 2 cycles after reaching cogwheel
bool step4[10]; //1 element per line  -- value for pellet presence 3 cycles after reaching cogwheel
bool step5[10]; //1 element per line  -- value for pellet presence 4 cycles after reaching cogwheel
bool step6[10]; //1 element per line  -- value for pellet presence 5 cycles after reaching cogwheel
bool step7[10]; //1 element per line  -- value for pellet presence 6 cycles after reaching cogwheel
bool step8[10]; //1 element per line  -- value for pellet presence 7 cycles after reaching cogwheel
bool step9[10]; //1 element per line  -- value for pellet presence 8 cycles after reaching cogwheel
bool step10[10]; //1 element per line  -- value for pellet presence 9 cycles after reaching cogwheel
bool step11[10]; //1 element per line  -- value for pellet presence when reaches scale

//------Shutdown Var's
int Error = 0;
int CogErrorFlg[10] = {0,0,0,0,0,0,0,0,0,0};
int ErrorCount = 10;

//--------


void setup() {
  //--------Scale Calibration Data
    //--------Scale 0
      ReadingA_Strain[0] = 29965866.00; //       <------------input scale raw reading for following weight here
      LoadA_Strain[0] = 1.0; //  (g) <-- calibration weight
      ReadingB_Strain[0] = 30139296.00; //       <------------input scale raw reading for following weight here
      LoadB_Strain[0] = 2.0; //  (g) <-- calibration weight
    //--------Scale 1
      ReadingA_Strain[1] = 866.0;
      LoadA_Strain[1] = 1.0; //  (g) 
      ReadingB_Strain[1] = 947.0;
      LoadB_Strain[1] = 2.0; //  (g) 
    //--------Scale 2
      ReadingA_Strain[2] = 866.0;
      LoadA_Strain[2] = 1.0; //  (g) 
      ReadingB_Strain[2] = 947.0;
      LoadB_Strain[2] = 2.0; //  (g) 
    //--------Scale 3
      ReadingA_Strain[3] = 866.0;
      LoadA_Strain[3] = 1.0; //  (g) 
      ReadingB_Strain[3] = 947.0;
      LoadB_Strain[3] = 2.0; //  (g) 
    //--------Scale 4
      ReadingA_Strain[4] = 866.0;
      LoadA_Strain[4] = 1.0; //  (g) 
      ReadingB_Strain[4] = 947.0;
      LoadB_Strain[4] = 2.0; //  (g) 
    //--------Scale 5
      ReadingA_Strain[5] = 866.0;
      LoadA_Strain[5] = 1.0; //  (g) 
      ReadingB_Strain[5] = 947.0;
      LoadB_Strain[5] = 2.0; //  (g) 
    //--------Scale 6
      ReadingA_Strain[6] = 866.0;
      LoadA_Strain[6] = 1.0; //  (g) 
      ReadingB_Strain[6] = 947.0;
      LoadB_Strain[6] = 2.0; //  (g) 
    //--------Scale 7
      ReadingA_Strain[7] = 866.0;
      LoadA_Strain[7] = 1.0; //  (g) 
      ReadingB_Strain[7] = 947.0;
      LoadB_Strain[7] = 2.0; //  (g) 
    //--------Scale 8
      ReadingA_Strain[8] = 866.0;
      LoadA_Strain[8] = 1.0; //  (g) 
      ReadingB_Strain[8] = 947.0;
      LoadB_Strain[8] = 2.0; //  (g) 
    //--------Scale 9
      ReadingA_Strain[9] = 866.0;
      LoadA_Strain[9] = 1.0; //  (g) 
      ReadingB_Strain[9] = 947.0;
      LoadB_Strain[9] = 2.0; //  (g) 
    

  //------Servo setup
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  //------Set up for Stepper Motor Controller
  pinMode (pulse, OUTPUT);
  pinMode (dir, OUTPUT);
  pinMode (en, OUTPUT);

  //------Set up for Reading Scales
  Wire.begin();
  adc.begin(ARD2499_ADC_ADDR_ZZZ, ARD2499_EEP_ADDR_ZZ);
  adc.ltc2499ChangeConfiguration(LTC2499_CONFIG2_60_50HZ_REJ);
  adc.ltc2499ChangeChannel(LTC2499_CHAN_SINGLE_0P);

  //------Set up for Selector Interrupt
  pinMode(SelectorInterruptPin0, INPUT_PULLUP);
  pinMode(SelectorInterruptPin1, INPUT_PULLUP);
  pinMode(SelectorInterruptPin2, INPUT_PULLUP);
  pinMode(SelectorInterruptPin3, INPUT_PULLUP);
  pinMode(SelectorInterruptPin4, INPUT_PULLUP);
  pinMode(SelectorInterruptPin5, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin0), Selector0, FALLING);
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin1), Selector1, FALLING);
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin2), Selector2, FALLING);
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin3), Selector3, FALLING);
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin4), Selector4, FALLING);
  attachInterrupt(digitalPinToInterrupt(SelectorInterruptPin5), Selector5, FALLING);
  
  //------Set up for Cogwheel Error Checking
  pinMode(inlet0, INPUT);
  pinMode(scale0, INPUT);
  pinMode(inlet1, INPUT);
  pinMode(scale1, INPUT);
  pinMode(inlet2, INPUT);
  pinMode(scale2, INPUT);
  pinMode(inlet3, INPUT);
  pinMode(scale3, INPUT);
  pinMode(inlet4, INPUT);
  pinMode(scale4, INPUT);
  pinMode(inlet5, INPUT);
  pinMode(scale5, INPUT);
  pinMode(inlet6, INPUT);
  pinMode(scale6, INPUT);
  pinMode(inlet7, INPUT);
  pinMode(scale7, INPUT);
  pinMode(inlet8, INPUT);
  pinMode(scale8, INPUT);
  pinMode(inlet9, INPUT);
  pinMode(scale9, INPUT);
}


void loop() {
  
  ScaleRead(); //Read all scales (values stored in "scale")
 
  for (int i = 0; i<=9; i++)
  {
    servo_control(i,scale[i]); //Set servos
  }

     //-------Cogwheel Control
  digitalWrite(dir, LOW);
  digitalWrite(en, HIGH);
  
  for (int i=0; i <= StepsPerIncrement; i++) {  //each pair of high/low digital writes causese 1 step
    digitalWrite(pulse, HIGH);
    digitalWrite(pulse, LOW);
    delay(6);
    if (i >= StepsPerIncrement-12) {
      switch (StepsPerIncrement-i) {
        case 0:
          delay(6);
        break;
        case 1:
          delay(6);
        break;
        case 2:
          delay(6);
        break;
        case 3:
          delay(5);
        break;
        case 4:
          delay(5);
        break;
        case 5:
          delay(4);
        break;
        case 6:
          delay(4);
        break;
        case 7:
          delay(3);
        break;
        case 8:
          delay(3);
        break;
        case 9:
          delay(2);
        break;
        case 10:
          delay(2);
        break;
        case 11:
          delay(1);
        break;
        case 12:
          delay(1);
        break;
      }
    }
  }
  delay(200);
  digitalWrite(dir, HIGH);
  for (int i=0; i <= 2*4; i++) {  //      <-- this pair of for loops does a short "back and forth" motion of the cog wheel to help with making sure the pellet entered the hole
    digitalWrite(pulse, HIGH);
    digitalWrite(pulse, LOW);
    delay(16);
  }
  delay(200);
  digitalWrite(dir, LOW);
  for (int i=0; i <= 1.25*4; i++) {
    digitalWrite(pulse, HIGH);
    digitalWrite(pulse, LOW);
    delay(16);
  }
  
  //-------Logic for Checking Bin Contents
  if((VeryLowCount >= binMax)||(LowCount >= binMax)||(GoodCount >= binMax)||(HighCount >= binMax)||(VeryHighCount>= binMax))
  {
    Bin_fill_shutdown;  //If the number of pellets in any bin exceeds the max number allowed, stop the machine
  }
  
  //-------Logic for Selector Interrupt
  if((sel1flg[0] != 1) || (sel1flg[1] != 1) || (sel1flg[2] != 1) || (sel1flg[3] != 1) || (sel1flg[4] != 1) \\ (sel1flg[5] != 1)) //if the beam was not tripped, the pellet did not exit the selector
  {
    //Problem between scale and selector exit!!!!
   Error++;
   if (Error = ErrorCount) {
    Selector_shutdown();
   }
  }
  else //if the beam was tripped, the pellet exited the selector
  {
    sel1flg = 0; //reset selector flag
    Error = 0;
  }
  
  //------Logic for Cogwheel Error Checking
  for (int i = 0; i<= 9; i++) //transfer pellet presence data down the line
  {
    step11[i] = step10[i];
    step10[i] = step9[i];
    step9[i] = step8[i];
    step8[i] = step7[i];
    step7[i] = step6[i];
    step6[i] = step5[i];
    step5[i] = step4[i];
    step4[i] = step3[i];
    step3[i] = step2[i];
    step2[i] = step1[i];
    step1[i] = step0[i];
  }

  step0[0] = digitalRead(inlet0);
  step0[1] = digitalRead(inlet1);
  step0[2] = digitalRead(inlet2);
  step0[3] = digitalRead(inlet3);
  step0[4] = digitalRead(inlet4);
  step0[5] = digitalRead(inlet5);
  step0[6] = digitalRead(inlet6);
  step0[7] = digitalRead(inlet7);
  step0[8] = digitalRead(inlet8);
  step0[9] = digitalRead(inlet9);
  
  CogError(scale,step11);  //if there is an issue due to missmatching, this function will stop the machine

  //------Bin Volume Output
  if ((VeryLowCount%100 == 0)||(LowCount%100 == 0)||(GoodCount%100 == 0)||(HighCount%100 == 0)||(VeryHighCount%100 == 0))
  {
    Serial.print("VeryLowCount = ");
    Serial.print(VeryLowCount);
    Serial.print("\t");
    Serial.print("LowCount = ");
    Serial.print(LowCount);
    Serial.print("\t");
    Serial.print("GoodCount = ");  //      counting the number of pellets sent to each bin
    Serial.print(GoodCount);
    Serial.print("\t");
    Serial.print("HighCount = ");
    Serial.print(HighCount);
    Serial.print("\t");
    Serial.print("VeryHighCount = ");
    Serial.print(VeryHighCount);
    Serial.print("\n");
  }
  
}//End of Main Loop


//------Servo Control Function
void servo_control(int servo, float val){  //positions selector servo based on the user set weight thresholds and the weight of the current pellet
  if ((val < 0.1)){  
    pwm.writeMicroseconds(servo, 0*(USMAX-USMIN)/4+USMIN);    
  }
  if ((0.1 <= val) && (val < VeryLow)){  
    pwm.writeMicroseconds(servo, 0*(USMAX-USMIN)/4+USMIN);    
    VeryLowCount++; // Increment count of pellets in Very Low Bin   
  }
  if ((val >= VeryLow) && (val < Low)){
    pwm.writeMicroseconds(servo, 1*(USMAX-USMIN)/4+USMIN);
    LowCount++; // Increment count of pellets in Low Bin
  }
  if ((val >= Low) && (val < High)){
    pwm.writeMicroseconds(servo, 2*(USMAX-USMIN)/4+USMIN);
    GoodCount++; // Increment count of pellets in Good Bin
  }
  if ((val >= High) && (val < VeryHigh)){
    pwm.writeMicroseconds(servo, 3*(USMAX-USMIN)/4+USMIN);
    HighCount++; // Increment count of pellets in High Bin
  }
  if ((val >= VeryHigh)){
    pwm.writeMicroseconds(servo, 4*(USMAX-USMIN)/4+USMIN);
    VeryHighCount++; // Increment count of pellets in Very High Bin
  } 
  
  return;
}

//------Load Cell Reading Function
void ScaleRead() {
  float ScaleVal[10] = {0,0,0,0,0,0,0,0,0,0};
  float sum[10] = {0,0,0,0,0,0,0,0,0,0};
  
  for (int i = 0; i<=scaleTime; i++) {
    ScaleVal[0] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_1P);
    sum[0] = sum[0] + ScaleVal[0];
    ScaleVal[1] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_2P);
    sum[1] = sum[1] + ScaleVal[1];
    ScaleVal[2] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_3P);
    sum[2] = sum[2] + ScaleVal[2];
    ScaleVal[3] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_4P);
    sum[3] = sum[3] + ScaleVal[3];
    ScaleVal[4] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_5P);
    sum[4] = sum[4] + ScaleVal[4];
    ScaleVal[5] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_6P);
    sum[5] = sum[5] + ScaleVal[5];
    ScaleVal[6] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_7P);
    sum[6] = sum[6] + ScaleVal[6];
    ScaleVal[7] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_8P);
    sum[7] = sum[7] + ScaleVal[7];
    ScaleVal[8] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_9P);
    sum[8] = sum[8] + ScaleVal[8];
    ScaleVal[9] = adc.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_0P);
    sum[9] = sum[9] + ScaleVal[9];
    delay(1);
  }

  for (int a = 0; a <= 9; a++) {
    ScaleVal[a] = sum[a]/scaleTime;
    Serial.print(ScaleVal[a]);
    Serial.print("\t");
    
    scale[a] = ((LoadB_Strain[a] - LoadA_Strain[a])/(ReadingB_Strain[a] - ReadingA_Strain[a])) * (ScaleVal[a] - ReadingA_Strain[a]) + LoadA_Strain[a];
  
    Serial.print(scale[a],3);
    Serial.print("\n");
  }
  
  return;
}

//------Bin Overfill Shutdown
void Bin_fill_shutdown() {
  while(1){
    if(VeryLowCount >= binMax){
      Serial.print("Very Low Bin Full");
    }
    if(LowCount >= binMax){
      Serial.print("Low Bin Full");
    }
    if(GoodCount >= binMax){
      Serial.print("Good Bin Full");
    }
    if(HighCount >= binMax){
      Serial.print("High Bin Full");
    }
    if(VeryHighCount >= binMax){
      Serial.print("Very High Bin Full");
    }
  }
}

//------Cogwheel Error Check
void CogError(float scale[10],bool stepLast[10]) {
  for (int i = 0; i<=9; i++)
  {
    if(scale[i] != 0 && stepLast[i] == 1)
    {
      //no issues
      CogErrorFlg[i] = 0;
    }
    else
    {
      //Issue between system inlet and scale!!!!
      CogErrorFlg[i]++;
      if (CogErrorFlg[i] == ErrorCount) {
        Cog_shutdown();
      }
    }
  }
}

//------Selector ISR
void Selector0() {
  sel1flg[0] = 1; //set flag when pellet exits selector
}
void Selector1() {
  sel1flg[1] = 1; //set flag when pellet exits selector
}
void Selector2() {
  sel1flg[2] = 1; //set flag when pellet exits selector
}
void Selector3() {
  sel1flg[3] = 1; //set flag when pellet exits selector
}
void Selector4() {
  sel1flg[4] = 1; //set flag when pellet exits selector
}
void Selector5() {
  sel1flg[5] = 1; //set flag when pellet exits selector
}

//------Cogwheel Shutdown
void Cog_shutdown() {
  while(1){
   Serial.print("Error at Cogwheel");
 }
}

//------Selector Shutdown
void Selector_shutdown(){
  while(1){
   Serial.print("Error at Selector");
 }   
}
