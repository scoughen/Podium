#include <Stepper.h>

const int stepsPerRevolution = 200;  // Steps per revolution of the motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  myStepper.setSpeed(60);  // sets the speed at 60 rpm
  Serial.begin(9600);  // serial port
}

void loop() {
  myStepper.step(10);  // steps taken 
  delay(500);  // wait 500 ms before repeating motion

}
