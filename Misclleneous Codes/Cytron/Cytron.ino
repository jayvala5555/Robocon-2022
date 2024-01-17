
 #include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor(PWM_DIR, 5, 6);  // PWM = Pin 3, DIR = Pin 4.


// The setup routine runs once when you press reset.
void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}


// The loop routine runs over and over again forever.
void loop() {
  motor.setSpeed(255);  // Run forward at 50% speed.
  delay(1000);
  motor.setSpeed(0);    // Stop.
  delay(1000);
//
//motor.setSpeed(-255);  // Run backward at 50% speed.
//delay(1000);
//motor.setSpeed(0);    // Stop.
//  delay(1000);
////  
//  motor.setSpeed(-255);  // Run backward at full speed.
//  delay(1000);
//
//  motor.setSpeed(0);    // Stop.
//  delay(1000);
}
