#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
}

void loop() {

int  pin2 = digitalRead(2);
int  pin3 = digitalRead(3);
int  pin4 = digitalRead(4);
int  pin5 = digitalRead(5);
int  pin6 = digitalRead(6);
  if (pin2 == 1 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 0)
  {
    myservo.write(0*255/5);              // tell servo to go to position 0
  }
  else if (pin2 == 0 && pin3 == 1 && pin4 == 0 && pin5 == 0 && pin6 == 0)
  {
    myservo.write(1*255/5);              // tell servo to go to position 1
  }
  else if (pin2 == 0 && pin3 == 0 && pin4 == 1 && pin5 == 0 && pin6 == 0)
  {
    myservo.write(2*255/5);              // tell servo to go to position 2
  }
  else if (pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 1 && pin6 == 0)
  {
    myservo.write(3*255/5);              // tell servo to go to position 3
  }
  else if (pin2 == 0 && pin3 == 0 && pin4 == 0 && pin5 == 0 && pin6 == 1)
  {
    myservo.write(5*255/5);              // tell servo to go to position 4
  }
}
