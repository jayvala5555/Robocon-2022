#include <EasyTransfer.h>

//***********
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#define READ_YawPitchRoll
#define READ_WORLDACCEL
#define INT_PIN 3
//#define LED 13

bool blink = false;
bool dmpready = false;
uint8_t mpuINTstatus;
uint8_t devstatus;
uint16_t packetsize;
uint16_t fifocount;
uint8_t fifobuffer[64];
int count;
//volatile double u = 0;
//volatile double v;
//volatile double a1;
//volatile double a2;
//volatile double Xx1;
//volatile double Xx;
//volatile double distancex;
//double t1 = 1/492.34;
Quaternion q;
VectorInt16 aa;
VectorInt16 aaReal;
VectorInt16 aaWorld;
VectorFloat gravity;
float eular[3];
float ypr[3];
volatile bool mpuINT = false;
void dmpdataready() {
  mpuINT = true;
}
//***********

EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float Yaw;
  float Pitch;
  float Roll;
  float AccX;
  float AccY;
  float AccZ;
};

//give a name to the group of data
SEND_DATA_STRUCTURE data;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(data), &Serial);

  //***********
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(100000);
  #endif

  Serial.begin(9600);
  while (!Serial);
  
  mpu.initialize();
  pinMode(INT_PIN, INPUT);

  //Serial.println("Testing device connections...");
  //Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  mpu.testConnection();
  //Serial.println(F("Initializing DMP..."));
  devstatus = mpu.dmpInitialize();

  mpu.setXAccelOffset(-4514);
  mpu.setYAccelOffset(-1781);
  mpu.setZAccelOffset(2912);
  mpu.setXGyroOffset(5);
  mpu.setYGyroOffset(-33);
  mpu.setZGyroOffset(33);

  if (devstatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();

    //Serial.println("Enabling DMP...");
    mpu.setDMPEnabled(true);

//    Serial.print("Enabling interrupt detection (Arduino external interrupt ");
//    Serial.print(digitalPinToInterrupt(INT_PIN));
//    Serial.println(")...");
    attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpdataready, RISING);
    mpuINTstatus = mpu.getIntStatus();

    //Serial.println("DMP ready! Waiting for first interrupt...");
    dmpready = true;

    packetsize = mpu.dmpGetFIFOPacketSize();
  } else {
    Serial.print("DMP Initialization failed");
    //Serial.print(devstatus);
    //Serial.println(")");
  }
  
}

void loop(){
  //this is how you access the variables. [name of the group].[variable name]
  if(!dmpready) return;

  if(mpu.dmpGetCurrentFIFOPacket(fifobuffer))
  {
    #ifdef READ_YawPitchRoll
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifobuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            //Serial.print("ypr\t");
            //Serial.println(ypr[0] * 180/M_PI);
//            Serial.print("\t");
//            Serial.print(ypr[1] * 180/M_PI);
//            Serial.print("\t");
//            Serial.println(ypr[2] * 180/M_PI);
              data.Yaw = ypr[0] * 180/M_PI;
              data.Pitch = ypr[1] * 180/M_PI;
              data.Roll = ypr[2] * 180/M_PI;
              Serial.print(data.Yaw);
        #endif
    
    #ifdef READ_WORLDACCEL
            mpu.dmpGetQuaternion(&q, fifobuffer);
            mpu.dmpGetAccel(&aa, fifobuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
//              Serial.print("aworld\t");
//              Serial.print(aaWorld.x*0.00059814453125);
//              Serial.print("\t");
//              Serial.print(aaWorld.y*0.00059814453125);
//              Serial.print("\t");
//              Serial.println(aaWorld.z*0.00059814453125);
                data.AccX = aaWorld.x*0.00059814453125;
                data.AccY = aaWorld.y*0.00059814453125;
                data.AccZ = aaWorld.z*0.00059814453125;
        #endif
  }
  //send the data
  ET.sendData();
  data.AccX = 0;
  data.AccY = 0;
  data.AccZ = 0;
  data.Yaw = 0;
  data.Pitch = 0;
  data.Roll = 0;
  delay(1000);
}
