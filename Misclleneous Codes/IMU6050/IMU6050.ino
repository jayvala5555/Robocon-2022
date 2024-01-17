#include <Wire.h>

float ACCX, ACCY, ACCZ, GYROX, GYROY, GYROZ;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  setupMPU();  // start serial for output
}

void loop() {
  accdata();
  gydata();
  printdata();
  delay(500);
}

void setupMPU()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00000000);
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x00000000);
  Wire.endTransmission();
}

void accdata()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  while(Wire.available()<6);
  ACCX = Wire.read()<<8|Wire.read();
  ACCY = Wire.read()<<8|Wire.read();
  ACCZ = Wire.read()<<8|Wire.read();
}

void gydata()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  while(Wire.available()<6);
  GYROX = Wire.read()<<8|Wire.read();
  GYROY = Wire.read()<<8|Wire.read();
  GYROZ = Wire.read()<<8|Wire.read();
}


void printdata()
{
  Serial.print("Acc(g): ");
  Serial.print("X=");
  Serial.print(ACCX/16384);
  Serial.print(" ");
  Serial.print("Y=");
  Serial.print(ACCY/16384);
  Serial.print(" ");
  Serial.print("Z=");
  Serial.println(ACCZ/16384);
  Serial.print("Gyro(deg): ");
  Serial.print("X=");
  Serial.print(GYROX/131);
  Serial.print(" ");
  Serial.print("Y=");
  Serial.print(GYROY/131);
  Serial.print(" ");
  Serial.print("Z=");
  Serial.println(GYROZ/131);
}
