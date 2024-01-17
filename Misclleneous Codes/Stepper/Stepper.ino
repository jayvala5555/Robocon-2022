#include<Stepper.h>
int steps=40;
int mspeed = 15;
Stepper my(steps, 8,9,10,11);
void setup() {
  Serial.begin(9600);
  my.setSpeed(mspeed);
}

void loop() {
  my.step(2);
  delay(2000);

}
