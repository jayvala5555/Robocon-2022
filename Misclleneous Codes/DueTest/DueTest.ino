#include <SPI.h>



void setup() {
  SerialUSB.begin(9600);

}

void loop() {
  SerialUSB.println("This is Arduino Due.");
  delay(500);
}
