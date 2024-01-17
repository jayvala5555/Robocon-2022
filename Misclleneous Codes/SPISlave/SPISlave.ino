#include <SPI.h>
float X, Y;
volatile byte Slavereceived;

void setup() {
  Serial.begin(9600);
  SPCR |= 1 << SPE;
//  SPI.attachInterrupt(); 
}

//ISR (SPI_STC_vect)                        //Inerrrput routine function 
//{
//  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
//                          //Sets received as True 
//}
void loop() {
//  float X[2];
//  for(int j = 0; j<2; j++){
//    X[j] == SPDR;
//    }
//  Serial.print("Value received:");
//  Serial.print(X[0]);
//  Serial.print(" ");
//  Serial.println(X[1]);

  int r;
  r = SPDR;
  Serial.println(r);
  

}
