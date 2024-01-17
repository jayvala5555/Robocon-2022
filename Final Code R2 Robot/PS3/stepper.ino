//void SteppermoveUp()
//{
//  int upval = PS3.getAnalogButton(DOWN);
//  //int downval = PS3.getAnalogButton(DOWN);
//  
//  if(upval>0){
//    int Movespeed1 = upval/160;
//    digitalWrite (ENgnd_u,LOW);
//    digitalWrite (EN_5v_u,LOW);
//    digitalWrite (DIRgnd_u,LOW);
//    digitalWrite (DIR_5v_u,LOW);
//    digitalWrite (ENgnd_d,LOW);
//    digitalWrite (EN_5v_d,LOW);
//    digitalWrite (DIRgnd_d,LOW);
//    digitalWrite (DIR_5v_d,LOW);
//    digitalWrite(STPgnd_u,LOW);
//    digitalWrite(STPgnd_d,LOW);
//    for(int x=0;)
//    digitalWrite (STP_5v_u, HIGH);
//    digitalWrite (STP_5v_d, HIGH);
//    delayMicroseconds(Movespeed1);
//    digitalWrite (STP_5v_u, LOW);
//    digitalWrite (STP_5v_d, LOW);
//    delayMicroseconds(Movespeed1);
//
//  }
//  
//  
//}
//
//void SteppermoveDown()
//{
//  //int upval = PS3.getAnalogButton(UP);
//  int downval = PS3.getAnalogButton(UP);
//  if(downval>0){
//    int Movespeed2 = downval/160; //3.9215686275;
//      digitalWrite (ENgnd_u,LOW);
//      digitalWrite (EN_5v_u,LOW);
//      digitalWrite (DIRgnd_u,LOW);
//      digitalWrite (DIR_5v_u,HIGH);
//      digitalWrite (ENgnd_d,LOW);
//      digitalWrite (EN_5v_d,LOW);
//      digitalWrite (DIRgnd_d,LOW);
//      digitalWrite (DIR_5v_d,HIGH);
//      digitalWrite(STPgnd_u,LOW);
//      digitalWrite(STPgnd_d,LOW);
//      digitalWrite (STP_5v_u, HIGH);
//      digitalWrite (STP_5v_d, HIGH);
//      delayMicroseconds(Movespeed2);
//      digitalWrite (STP_5v_u, LOW);
//      digitalWrite (STP_5v_d, LOW);
//      delayMicroseconds(Movespeed2);
//      //SW ON = 236 OFF = 145
//    }
//    
//  
//}
//
//
//void SteppermoveRight()
//{
//  int rightval = PS3.getAnalogButton(RIGHT);
//  //int downval = PS3.getAnalogButton(DOWN);
//  
//  if(rightval>0){
//    int Movespeed3 = rightval/20;
//    digitalWrite (ENgnd_lr,LOW);
//    digitalWrite (EN_5v_lr,LOW);
//    digitalWrite (DIRgnd_lr,LOW);
//    digitalWrite (DIR_5v_lr,LOW);
//    digitalWrite(STPgnd_lr,LOW);
//    digitalWrite(STP_5v_lr, HIGH);
//    delayMicroseconds(Movespeed3);
//    digitalWrite (STP_5v_lr, LOW);
//    delayMicroseconds(Movespeed3);
//  }
//  
//}
//
//void SteppermoveLeft()
//{
//  int leftval = PS3.getAnalogButton(LEFT);
//  //int downval = PS3.getAnalogButton(DOWN);
//  
//  if(leftval>0){
//    int Movespeed4 = leftval/20;
//    digitalWrite (ENgnd_lr,LOW);
//    digitalWrite (EN_5v_lr,LOW);
//    digitalWrite (DIRgnd_lr,LOW);
//    digitalWrite (DIR_5v_lr,HIGH);
//    digitalWrite(STPgnd_lr,LOW);
//    digitalWrite(STP_5v_lr, HIGH);
//    delayMicroseconds(Movespeed4);
//    digitalWrite (STP_5v_lr, LOW);
//    delayMicroseconds(Movespeed4);
//  }
//  
//}
  

//servo code
void servoUP()
{
  servos.write(80);
  }

void servoDOWN()
{
  servos.write(170);
  }
