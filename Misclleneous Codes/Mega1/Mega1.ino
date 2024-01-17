int values[3] = {0};
void setup() {
  Serial.begin(9600);
  
}

void loop() {

  if(Serial.available()>0)
  {
    for(int j=0;j<3;j++){
      values[j] = Serial.read();}
    Serial.print("Data Received:");
    for(int i=0;i<3;i++){
      Serial.println(values[i]);
      }
    }
  
  
}
