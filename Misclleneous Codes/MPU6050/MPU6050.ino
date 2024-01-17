#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#define READ_YawPitchRoll
#define READ_WORLDACCEL
#define OUTPUT_READABLE_REALACCEL
#define INT_PIN 3
#define LED 13

bool blink = false;
bool dmpready = false;
uint8_t mpuINTstatus;
uint8_t devstatus;
uint16_t packetsize;
uint16_t fifocount;
uint8_t fifobuffer[64];
int count;
volatile double u = 0;
volatile double v;
volatile double a1;
volatile double a2;
volatile double Xx1;
volatile double Xx;
//volatile double t2=0;
volatile double distancex;
double t1 = 1/492.34;
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


void setup()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(100000);
#endif

  Serial.begin(115200);
  while (!Serial);

  Serial.println("Initializing I2C devices...");
  mpu.initialize();
  pinMode(INT_PIN, INPUT);

  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  

  Serial.println(F("Initializing DMP..."));
  devstatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(64);
  mpu.setYGyroOffset(27);
  mpu.setZGyroOffset(-37);
  mpu.setZAccelOffset(628);
  mpu.setYAccelOffset(-1201);
  mpu.setXAccelOffset(-298);

  if (devstatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    

    Serial.println("Enabling DMP...");
    mpu.setDMPEnabled(true);

    Serial.print("Enabling interrupt detection (Arduino external interrupt ");
    Serial.print(digitalPinToInterrupt(INT_PIN));
    Serial.println(")...");
    attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpdataready, RISING);
    mpuINTstatus = mpu.getIntStatus();

    Serial.println("DMP ready! Waiting for first interrupt...");
    dmpready = true;

    packetsize = mpu.dmpGetFIFOPacketSize();
  } else {
    Serial.print("DMP Initialization failed (code");
    Serial.print(devstatus);
    Serial.println(")");
  }
  pinMode(LED, OUTPUT);

}

void loop()
{
  
  if(!dmpready) return;

  if(mpu.dmpGetCurrentFIFOPacket(fifobuffer))
  {
    #ifdef READ_YawPitchRoll
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifobuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
//            Serial.print("ypr\t");
//            Serial.print(ypr[0] * 180/M_PI);
//            Serial.print("\t");
//            Serial.print(ypr[1] * 180/M_PI);
//            Serial.print("\t");
//            Serial.println(ypr[2] * 180/M_PI);
        #endif
    
    #ifdef READ_WORLDACCEL
            mpu.dmpGetQuaternion(&q, fifobuffer);
            mpu.dmpGetAccel(&aa, fifobuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
              Serial.print("aworld\t");
              Serial.print(aaWorld.x*0.00059814453125);
              Serial.print("\t");
              Serial.print(aaWorld.y*0.00059814453125);
              Serial.print("\t");
              Serial.println(aaWorld.z*0.00059814453125);
        #endif

    #ifdef OUTPUT_READABLE_REALACCEL
            // display real acceleration, adjusted to remove gravity
            mpu.dmpGetQuaternion(&q, fifobuffer);
            mpu.dmpGetAccel(&aa, fifobuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
//            Serial.print("areal\t");
//            Serial.print(aaReal.x*0.00059814453125*2);
//            Serial.print("\t");
//            Serial.print(aaReal.y*0.00059814453125*2);
//            Serial.print("\t");
//            Serial.println(aaReal.z*0.00059814453125*2);
        #endif
        a2 = aaWorld.x*0.00059814453125*2;
        //v = u + (aaReal.x*0.00059814453125*2)*t1;
        //Xx = (u*t1) + 0.5*(aaWorld.x*0.00059814453125)*(t1*t1);
        //Xx = (v*v - u*u)/2*(aaReal.x*0.00059814453125*2);

        v = u + (((a2+a1)*t1)/2);
        Xx = u*t1 + (((v + u)*t1)/2);
        distancex = distancex + Xx;
        Serial.println(distancex);
        blink = !blink;
        digitalWrite(LED, blink);
        
    }
    u = v;
    Xx1 = Xx;
    a1 = a2;

  
  }
