#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define USMIN  1000 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  1500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define servo0  0 // servo being driven
#define servo1  1 // servo being driven
#define servo2  2 // servo being driven
#define servo3  4 // servo being driven
#define servo4  5 // servo being driven
#define servo5  6 // servo being driven

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {
  pwm.writeMicroseconds(servo0, 0*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo1, 0*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo2, 0*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo3, 0*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo4, 0*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo5, 0*(USMAX-USMIN)/4+USMIN);
  delay(1000);
  pwm.writeMicroseconds(servo0, 1*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo1, 1*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo2, 1*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo3, 1*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo4, 1*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo5, 1*(USMAX-USMIN)/4+USMIN);
  delay(1000);
  pwm.writeMicroseconds(servo0, 2*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo1, 2*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo2, 2*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo3, 2*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo4, 2*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo5, 2*(USMAX-USMIN)/4+USMIN);
  delay(1000);
  pwm.writeMicroseconds(servo0, 3*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo1, 3*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo2, 3*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo3, 3*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo4, 3*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo5, 3*(USMAX-USMIN)/4+USMIN);
  delay(1000);
  pwm.writeMicroseconds(servo0, 4*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo1, 4*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo2, 4*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo3, 4*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo4, 4*(USMAX-USMIN)/4+USMIN);
  pwm.writeMicroseconds(servo5, 4*(USMAX-USMIN)/4+USMIN);
  delay(1000);
}
