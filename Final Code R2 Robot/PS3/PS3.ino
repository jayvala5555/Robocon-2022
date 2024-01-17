/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */
//=======================================//
//========== Include Libraries ==========//
#include <PS3BT.h> //https://github.fcom/felis/USB_Host_Shield_2.0/blob/master/PS3BT.h
#include <usbhub.h>
#include <EasyTransfer.h>
#include <Servo.h>
Servo servos;

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>
//=======================================//
//========== Defining ==========//
#define BluetoothSerial Serial //Serial3 will be used in another arduino (upper control) to receive data from this arduino (ps3's arduino)

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
PS3BT PS3(&Btd, 0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x10); // PR
//PS3BT PS3(&Btd);
//PS3BT PS3(&Btd, 0x60, 0x38, 0x0E, 0x97, 0x90, 0x4D);

//==============================//
//========== Structure to send ==========//
struct PS3_data {
  float ps3data;
  int pwm1;
  int pwm2;
  int pwm3;
};
PS3_data data;
//=======================================//

//========== Switches ==========//
enum value {noData, leftx, upx, rightx, downx, selectx, psx, startx, squarex, trianglex, circlex, crossx, l1x, l2x, l3x, r1x, r2x, r3x};
value PS3Val = noData;
//==============================//

//=======================Variables================//

int LeftAnalogDataX;
int LeftAnalogDataY;

int RightAnalogDataX;
int RightAnalogDataY;

float vel1;
float vel2;
float vel3;

int PWM1;
int PWM2;
int PWM3;

float theta1;
float theta2;
float theta3;

//float dt = 0.001;
float OmegaOfBot = 0; // Initialise with zero
float RadiusOfBot = 0.65; // Predefined value 0.650 m
float MaxOmegaOfBot = 7.34649359; //Predefined Value //(MaxOmegaOfOneMotor * RadiusOfOmniWheel / RadiusOfBot) // RadiusOfOmniWheel 0.076 m  // MaxOmegaOfOneMotor (600rpm) =>(600*2*Pi rad/min) =>(600*2*Pi/60 rad/sec) =>(62.8318531) //
float MaxVx = 4.775220833; // Predefined Value // (v1) //MaxOmegaOfOneMotor * RadiusOfOmniWheel (62.8318531 * 0.076)*4/3
float MaxVy = 2.756975032;  //Predefined Value // (v1 /  root3) // v1=4.775220833
float MaxV1 = 4.775220833;
//MaxOmegaOfOneMotor = 
EasyTransfer ET_ps3;
//=====================================//
//Stepper pins declaration
#define ENgnd_u  22 //ENA-(ENA) stepper motor enable , active low 
#define EN_5v_u  24 //ENA+(+5V) stepper motor enable , active low
#define DIRgnd_u 26 //DIR-(DIR) axis stepper motor direction control
#define DIR_5v_u 28 //DIR+(+5v) axis stepper motor direction control
#define STPgnd_u 30 //PUL-(PUL) axis stepper motor step control
#define STP_5v_u 32 //PUL+(+5v) axis stepper motor step control

#define ENgnd_d  23 //ENA-(ENA) stepper motor enable , active low 
#define EN_5v_d  25 //ENA+(+5V) stepper motor enable , active low
#define DIRgnd_d 27 //DIR-(DIR) axis stepper motor direction control
#define DIR_5v_d 29 //DIR+(+5v) axis stepper motor direction control
#define STPgnd_d 31 //PUL-(PUL) axis stepper motor step control
#define STP_5v_d 33 //PUL+(+5v) axis stepper motor step control

#define ENgnd_lr  34 //ENA-(ENA) stepper motor enable , active low 
#define EN_5v_lr  35 //ENA+(+5V) stepper motor enable , active low
#define DIRgnd_lr 36 //DIR-(DIR) axis stepper motor direction control
#define DIR_5v_lr 37 //DIR+(6++5v) axis stepper motor direction control
#define STPgnd_lr 38 //PUL-(PUL) axis stepper motor step control
#define STP_5v_lr 39 //PUL+(+5v) axis stepper motor step control

#define Pneu1up 41
#define Pneu1down 42
#define Pneu2up 43
#define Pneu2down 40

#define Pwm1 2
#define Pwm2 44
#define Pwm3 46

#define Dir1 47
#define Dir2 48
#define Dir3 49




int i = 0;
void setup() {
  
  servos.attach(40);
  //==============Variable Initialisation=============//
  vel1 = 0; //vel of wheel 1
  vel2 = 0; //vel of wheel 2
  vel3 = 0; //vel of wheel 3

  theta1 = (3.14159265 / 2);                          //pi/2
  theta2 = ((3.14159265 / 2) + (2 * 3.14159265 / 3)); //pi/2 + 2pi/3
  theta3 = ((3.14159265 / 2) + (4 * 3.14159265 / 3)); //pi/2 + 4pi/3
  //==================================================//
   pinMode (ENgnd_u,OUTPUT); //ENA-(ENA)
   pinMode (EN_5v_u,OUTPUT); //ENA+(+5V)
   pinMode (DIRgnd_u,OUTPUT); //DIR-(DIR)
   pinMode (DIR_5v_u,OUTPUT); //DIR+(+5v)
   pinMode (STPgnd_u,OUTPUT); //PUL-(PUL)
   pinMode (STP_5v_u,OUTPUT); //PUL+(+5v)
  
   pinMode (ENgnd_d,OUTPUT); //ENA-(ENA)
   pinMode (EN_5v_d,OUTPUT); //ENA+(+5V)
   pinMode (DIRgnd_d,OUTPUT); //DIR-(DIR)
   pinMode (DIR_5v_d,OUTPUT); //DIR+(+5v)
   pinMode (STPgnd_d,OUTPUT); //PUL-(PUL)
   pinMode (STP_5v_d,OUTPUT); //PUL+(+5v)

   pinMode(Pwm1,OUTPUT);
   pinMode(Pwm2,OUTPUT);
   pinMode(Pwm3,OUTPUT);
   pinMode(Dir1,OUTPUT);
   pinMode(Dir2,OUTPUT);
   pinMode(Dir3,OUTPUT);
   
  digitalWrite (ENgnd_u,  LOW); //ENA-(ENA)
  digitalWrite (EN_5v_u, HIGH); //ENA+(+5V) low=enabled
  digitalWrite (DIRgnd_u, LOW); //DIR-(DIR)
  digitalWrite (DIR_5v_u, LOW); //DIR+(+5v)
  digitalWrite (STPgnd_u, LOW); //PUL-(PUL)
  digitalWrite (STP_5v_u, LOW); //PUL+(+5v)

  digitalWrite (ENgnd_d,  LOW); //ENA-(ENA)
  digitalWrite (EN_5v_d, HIGH); //ENA+(+5V) low=enabled
  digitalWrite (DIRgnd_d, LOW); //DIR-(DIR)
  digitalWrite (DIR_5v_d, LOW); //DIR+(+5v)
  digitalWrite (STPgnd_d, LOW); //PUL-(PUL)
  digitalWrite (STP_5v_d, LOW); //PUL+(+5v)

  pinMode (ENgnd_lr,OUTPUT); //ENA-(ENA)
  pinMode (EN_5v_lr,OUTPUT); //ENA+(+5V)
  pinMode (DIRgnd_lr,OUTPUT); //DIR-(DIR)
  pinMode (DIR_5v_lr,OUTPUT); //DIR+(+5v)
  pinMode (STPgnd_lr,OUTPUT); //PUL-(PUL)
  pinMode (STP_5v_lr,OUTPUT); //PUL+(+5v)
  pinMode (Pneu1up, OUTPUT);
  pinMode (Pneu1down, OUTPUT);
  pinMode (Pneu2up, OUTPUT);
  pinMode (Pneu2down, OUTPUT);

  digitalWrite (ENgnd_lr,  LOW); //ENA-(ENA)
  digitalWrite (EN_5v_lr, HIGH); //ENA+(+5V) low=enabled
  digitalWrite (DIRgnd_lr, LOW); //DIR-(DIR)
  digitalWrite (DIR_5v_lr, LOW); //DIR+(+5v)
  digitalWrite (STPgnd_lr, LOW); //PUL-(PUL)
  digitalWrite (STP_5v_lr, LOW); //PUL+(+5v)
  digitalWrite (Pneu1up, LOW);
  digitalWrite (Pneu1down, LOW);
  digitalWrite (Pneu2up, LOW);
  digitalWrite (Pneu2down, LOW);
  // put your setup code here, to run once:
  Serial.begin(115200);
  BluetoothSerial.begin(115200);
  ET_ps3.begin(details(data),&BluetoothSerial);
  Serial.println("IN SETUP");

  #if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif

  if (Usb.Init() == -1) 
    {
      Serial.print(F("\r\nOSC did not start"));
      while (1); //halt
    }
    Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite (Pneu1up, LOW);
  digitalWrite (Pneu1down, LOW);
  digitalWrite (Pneu2up, LOW);
  digitalWrite (Pneu2down, LOW);
  Serial.println("In Loop");
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  {
    Serial.println("Connected");
    receivePS3data();
       
    data.ps3data = PS3Val;
    data.pwm1 = int((vel1/MaxV1)*150);
    data.pwm2 = int((vel2/MaxV1)*150);
    data.pwm3 = int((vel3/MaxV1)*150);

    PWM1 = int((vel1/MaxV1)*150);
    PWM2 = int((vel2/MaxV1)*150);
    PWM3 = int((vel3/MaxV1)*150);

//    Serial.print("PWM 1 :");
//    Serial.print(data.pwm1);
//    Serial.println("");
//    Serial.print("PWM 2 :");
//    Serial.print(data.pwm2);
//    Serial.println("");
//    Serial.print("PWM 3 :");
//    Serial.print(data.pwm3);
//    Serial.println("");
    
    Serial.println("Sending Data");
    ET_ps3.sendData();
    Serial.println("Done");
    BluetoothSerial.flush();
  
    if (PS3.PS3Connected)
    {
      if (PS3.getButtonClick(PS))
      {
         Serial.println("Disconnect");
         PS3.disconnect();
      }
    }
    Serial.print("PWM1: ");
    Serial.print(PWM1);
    Serial.print(" PWM2: ");
    Serial.print(PWM2);
    Serial.print(" PWM3: ");
    Serial.print(PWM3);
    Serial.print("\n");
    
    if(PWM1>0)
    {
      digitalWrite(Dir1, HIGH);
    }
    if(PWM2>0)
    {
      digitalWrite(Dir2, HIGH);
    }
    if(PWM3>0)
    {
      digitalWrite(Dir3, HIGH);
    }
    if(PWM1<=0)
    {
      digitalWrite(Dir1, LOW);
    }
    if(PWM2<=0)
    {
      digitalWrite(Dir2, LOW);
    }
    if(PWM3<=0)
    {
      digitalWrite(Dir3, LOW);
    }
    analogWrite(Pwm1, PWM1);
    analogWrite(Pwm2, PWM2);
    analogWrite(Pwm3, PWM3);
    }
} 
