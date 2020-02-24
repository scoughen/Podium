#include <Servo.h>

Servo servo_1;  //Create servo object to control first servo

int pos = 0;  //Integer value for servo position

int potpin = 0;  //potentiometrer attached to analog pin zero
int val;  //variable to read value from the analogue pin


void setup() {
  // put your setup code here, to run once:
servo_1.attach();  //Servo 1 is attached to pin
servo_2.attach();  //Servo 2 is attached to pin 
servo_3.attach();  //Servo 3 is attached to pin
servo_4.attach();  //Servo 4 is attached to pin
servo_5.attach();  //Servo 5 is attached to pin
servo_6.attach();  //Servo 6 is attached to pin
servo_7.attach();  //Servo 7 is attached to pin
servo_8.attach();  //Servo 8 is attached to pin
servo_9.attach();  //Servo 9 is attached to pin
servo_10.attach();  //Servo 10 is attached to pin
}



void loop() {
  // put your main code here, to run repeatedly:

}

//Servo 1 Function
float servo_control_1(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
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

//Servo 2 Function
float servo_control_2(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//Servo 3 Function
float servo_control_3(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//servo 4 Function
float servo_control_3(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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
//Servo 5 Function
float servo_control_5(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//Servo 6 function
float servo_control_6(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//Servo 7 Function
float servo_control_7(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//Servo 9 Function
float servo_control_9(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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

//Servo 10 Function
float servo_control_10(){
int val = analogRead(potpin);  //Reads value of potentiometer (value between 0 and 1023)
val = map(val,0,1023,0,180);
if ((val >=0) && (val <36)){  //
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


}
