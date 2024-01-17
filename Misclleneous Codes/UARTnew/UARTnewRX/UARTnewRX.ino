#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  float Yaw;
  float Pitch;
  float Roll;
  float AccX;
  float AccY;
  float AccZ;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE data;

void setup(){
  Serial.begin(9600);
  //Serial1.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(data), &Serial);
  
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    Serial.print("Yaw\t");
    Serial.print(data.Yaw);
    Serial.print("\tPitch\t");
    Serial.print(data.Pitch);
    Serial.print("\tRoll\t");
    Serial.println(data.Roll);
    Serial.print("AccX\t");
    Serial.print(data.AccX);
    Serial.print("\tAccY\t");
    Serial.print(data.AccY);
    Serial.print("\tAccZ\t");
    Serial.println(data.AccZ);
  }
  
  delay(1000);
}
