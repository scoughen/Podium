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
}


void loop() {
  servo_control_1();
  servo_control_2();
  servo_control_3();
  servo_control_4();
  servo_control_5();
  servo_control_6();
  servo_control_7();
  servo_control_8();
  servo_control_9();
  servo_control_10();
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
<<<<<<< HEAD
return val;  
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

}
//Servo 2 Function
<<<<<<< HEAD
float servo_control_2(){
=======
  float servo_control_2(){
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba
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
<<<<<<< HEAD
return val;
}
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
return val;
}
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
return val;
}

=======
  
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba
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
<<<<<<< HEAD
return val;
}
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
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
=======

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
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
return val;
}
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
return val;
}
=======
>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba

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
<<<<<<< HEAD
}
retun val;
=======
  }


>>>>>>> f4aa762590d1cce244145a50c90760f1e2565cba
}
