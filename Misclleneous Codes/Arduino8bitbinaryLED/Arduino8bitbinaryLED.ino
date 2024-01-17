void setup() 
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  byte y = 22;
  for(int i=0; i<=7; i++)
  {
    bool m = bitRead(y, i);
    int j = i+6;
    if(m==1){
    digitalWrite(j,HIGH);
    }
    else
    {
      digitalWrite(j,LOW);
    }
  }
  delay(1000);
  
}
