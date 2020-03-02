#include <Stepper.h>
#define stepsPerRev 200;  // Steps per revolution of the motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRev, 8, 9, 10, 11);

void setup() {
  myStepper.setSpeed(60);  // sets the speed at 60 rpm
  Serial.begin(9600);  // serial port
}

void loop() {
  myStepper.step(10);  // steps taken
  delay(1000);  // wait one second before repeating motion

}


// Change stepsPerRev to our motor (can be modified with gear reduction for more steps)
// Need to determine how many steps necessary to rotate barrel to each cutout
