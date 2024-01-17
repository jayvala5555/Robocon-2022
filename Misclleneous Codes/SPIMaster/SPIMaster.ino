#include <SPI.h>

void setup() {
  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  digitalWrite(SS, LOW);
//  float x[2] = {0.01, 0.02};
//  for(int i=0; i <2; i++) {
//  SPI.transfer(x[i]);
//    }
  int d = 10;
  SPI.transfer(d);
  digitalWrite(SS, LOW);

  
  delay(1000);
}
