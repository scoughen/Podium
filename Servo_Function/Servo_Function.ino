#include <Servo.h>

Servo servo_1;  //Create servo object to control first servo

int pos = 0;  //Integer value for servo position

int potpin = 0;  //potentiometrer attached to analog pin zero
int val;  //variable to read value from the analogue pin


void setup() {
  // put your setup code here, to run once:
 servo_1.attach(9);  //Servo 1 is attached to pin 9

}


void loop() {
  // put your main code here, to run repeatedly:

}

void servo_control(int val){
val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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
}
