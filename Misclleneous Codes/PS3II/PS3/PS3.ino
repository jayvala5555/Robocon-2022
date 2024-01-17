

/*
  Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
  For more information visit my blog: http://blog.tkjelectronics.dk/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <PS3BT.h>
#include <usbhub.h>
#include <EasyTransfer.h>
#include <Wire.h>
//i2c
#include <EasyTransferI2C.h>

//create object
EasyTransferI2C ET;

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float velocity1;
  float velocity2;
  float velocity3;
};
//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
//define slave i2c address
#define I2C_SLAVE_ADDRESS 9
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
float t = 0, v1 = 0, v2 = 0, v3 = 0;
float velocity1, velocity2, velocity3;

//MOTOR DRIVER PINS
//int enA = 11;
//int motorApin1 = 8;
//int motorApin2 = 7;
//int enB = 10;
//int motorBpin1 = 6;
//int motorBpin2 = 5;
//int enC = 9;
//int motorCpin1 = 4;
//int motorCpin2 = 3;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  //i2c
  Wire.begin();
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    ET.begin(details(mydata), &Wire);
  randomSeed(analogRead(0));

  //PWM
//  pinMode(enA, OUTPUT);
//  pinMode(motorApin1, OUTPUT);
//  pinMode(motorApin2, OUTPUT);
//  pinMode(enB, OUTPUT);
//  pinMode(motorBpin1, OUTPUT);
//  pinMode(motorBpin2, OUTPUT);
//  pinMode(enC, OUTPUT);
//  pinMode(motorCpin1, OUTPUT);
//  pinMode(motorCpin2, OUTPUT);
//
//  digitalWrite(motorApin1, LOW);
//  digitalWrite(motorApin2, LOW);
//  digitalWrite(motorBpin1, LOW);
//  digitalWrite(motorBpin2, LOW);
//  digitalWrite(motorCpin1, LOW);
//  digitalWrite(motorCpin2, LOW);
}
void loop() {
  Usb.Task();
  calc();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    //if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {

    ps3_fns();
  }

  Serial.println(String(v1) + " " + String(v2) + " " + String(v3));

  // Analog button values can be read from almost all buttons
  if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
    Serial.print(F("\r\nL2: "));
    Serial.print(PS3.getAnalogButton(L2));
    if (PS3.PS3Connected) {
      Serial.print(F("\tR2: "));
      Serial.print(PS3.getAnalogButton(R2));
    }
  }


  //Serial.write("theta");
  //this is how you access the variables. [name of the group].[variable name]
  mydata.velocity1 = (v1 * 255) / 4.775220833;
  mydata.velocity2 = (v2 * 255) / 4.775220833;
  mydata.velocity3 = (v3 * 255) / 4.775220833;
  //send the data
   ET.sendData(I2C_SLAVE_ADDRESS);

}
