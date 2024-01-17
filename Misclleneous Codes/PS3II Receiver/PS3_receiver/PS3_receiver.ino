#include <Wire.h>

#include <EasyTransferI2C.h>

//create object
EasyTransferI2C ET;

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float velocity1;
  float velocity2;
  float velocity3;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

int enA = 11;
int motorApin1 = 8;
int motorApin2 = 7;
int enB = 10;
int motorBpin1 = 6;
int motorBpin2 = 5;
int enC = 9;
int motorCpin1 = 4;
int motorCpin2 = 3;
 
void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SLAVE_ADDRESS);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Wire);
  //define handler function on receiving data
  Wire.onReceive(receive);

  pinMode(enA, OUTPUT);
  pinMode(motorApin1, OUTPUT);
  pinMode(motorApin2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(motorBpin1, OUTPUT);
  pinMode(motorBpin2, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(motorCpin1, OUTPUT);
  pinMode(motorCpin2, OUTPUT);

  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, LOW);
  digitalWrite(motorCpin1, LOW);
  digitalWrite(motorCpin2, LOW);

}

void loop() {
  //check and see if a data packet has come in.
  if (ET.receiveData() > 0) {
    //this is how you access the variables. [name of the group].[variable name]
    Serial.print(mydata.velocity1);
    Serial.print(" ");
    Serial.print(mydata.velocity2);
    Serial.print(" ");
    Serial.println(mydata.velocity3);

    if (mydata.velocity1 > 0) {
      digitalWrite(motorApin1, HIGH);
      digitalWrite(motorApin2, LOW);
    }
    if(mydata.velocity1 < 0) {
      digitalWrite(motorApin1, LOW);
      digitalWrite(motorApin2, HIGH);
    }
    if(mydata.velocity1 == 0) {
      digitalWrite(motorApin1, HIGH);
      digitalWrite(motorApin2, HIGH);
    }
    
    if (mydata.velocity2 > 0) {
      digitalWrite(motorBpin1, HIGH);
      digitalWrite(motorBpin2, LOW);
    }
    if(mydata.velocity2 < 0) {
      digitalWrite(motorBpin1, LOW);
      digitalWrite(motorBpin2, HIGH);
    }
    if(mydata.velocity2 == 0) {
      digitalWrite(motorBpin1, HIGH);
      digitalWrite(motorBpin2, HIGH);
    }

    if (mydata.velocity3 > 0) {
      digitalWrite(motorCpin1, HIGH);
      digitalWrite(motorCpin2, LOW);
    }
    if(mydata.velocity3 < 0) {
      digitalWrite(motorCpin1, LOW);
      digitalWrite(motorCpin2, HIGH);
    }
    if(mydata.velocity3 == 0) {
      digitalWrite(motorCpin1, HIGH);
      digitalWrite(motorCpin2, HIGH);
    }

    analogWrite(enA, mydata.velocity1);
    analogWrite(enB, mydata.velocity2);
    analogWrite(enC, mydata.velocity3);

  }
}


void receive(int numBytes) {}
