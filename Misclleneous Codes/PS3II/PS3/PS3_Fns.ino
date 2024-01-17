float w=0, r=0.065, a=0;     //fixing the value of w and r
float theta=1.0466666667;   //initial theta=pi/3 as the angle between driving velocity and x-axis

int n=0, v_x=0, v_y=0;
int left_xaxis=0 , left_yaxis=0;

void calc()
{
 if (PS3.PS3Connected || PS3.PS3NavigationConnected){
   left_xaxis=PS3.getAnalogHat(LeftHatX);
   left_yaxis=PS3.getAnalogHat(LeftHatY);

   //MAPPING
  
   v_x = map(left_xaxis,0,255,-255,255);
   v_y = map(left_yaxis,255,0,255,-255);
   //Serial.println(String(v_x) + " " + String(v_y));
   v_x= (v_x*4.775220833)/255;   //max velocity of bot in x axis = max velocity of wheel (V = 4.775220833)
   v_y= (v_y*2.756975034)/255;   //max velocity of bot in y axis = max velocity of wheel/root 3 (V/1.73 = 2.75695034)

   if(PS3.getButtonClick(CIRCLE)){
      w=10;
      n=PS3.getAnalogButton(CIRCLE);   // storing the analog value of circle in variable n
      t=(n*0.628)/255;                 //considering w=10 and and angle max angle 2*pi, max time = (2*pi)/w = 0.628
      theta=w*t;
      a=theta;
      theta=a+theta;
      
    }
    
   else{
    w=0;
    }
   //Serial.print(String(theta));
   //Serial.print(((theta+2.094)*360)/6.28);
   
   v1= v_x*cos(theta) + v_y*sin(theta) + w*r;  //theta is angle between driving velocity and x-axis
   v2= v_x*cos(theta+2.094) + v_y*sin(theta+2.094) + w*r; //angle b/w 2nd wheel's driving velocity and x-axis = theta + (2*pi)/3
   v3= v_x*cos(theta+4.187) + v_y*sin(theta+4.187) + w*r; //angle b/w 3nd wheel's driving velocity and x-axis = theta + (4*pi)/3
  } 
}

void ps3_fns(){
 if (PS3.PS3Connected || PS3.PS3NavigationConnected){
  if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      /*if (PS3.getButtonClick(CIRCLE)) {
      n=PS3.getAnalogButton(CIRCLE);   // storing the analog value of circle in variable n
      t=(n*0.628)/255;                 //considering w=10 and and angle max angle 2*pi, max time = (2*pi)/w = 0.628
      theta=w*t;
      }*/
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        //PS3.setRumbleOn(RumbleLow);
      }
      //if (PS3.getButtonClick(CIRCLE)) {
        //Serial.print(F("\r\nCircle"));
        //PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS))
        Serial.print(F("\r\nCross"));
      if (PS3.getButtonClick(SQUARE))
        Serial.print(F("\r\nSquare"));

      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }

      if (PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS3.getButtonClick(R3)){
        Serial.print(F("\r\nR3"));
      }

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
  }

  
}
