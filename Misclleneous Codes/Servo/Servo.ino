#include<Servo.h>
Servo servo1;
//Servo servo2;
void setup() {
  servo1.attach(6);

}

void loop() {
    servo1.write(80);
   // servo2.write(85);
    delay(1000);
    servo1.write(170);
   // servo2.write(160);
    delay(1000);
//    servo1.write(45);0

//    delay(1000);
//    servo1.write(148);
//    delay(1000);

      // servo1 LEFT UP 75 to DOWN 160
      // servo2 RIGHT UP 170 to DOWN 85
}
