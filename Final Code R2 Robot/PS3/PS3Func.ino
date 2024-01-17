/*
       0 
       | 
       | 
0------|------255
       |
       |
       255

*/
void receivePS3data()
{
    OmegaOfBot = 0;
    //Serial.println("In iffff");
    
    //========== R L U D ==========//
    if(PS3.getButtonPress(RIGHT)) 
    {
        Serial.println("Right");
        PS3Val = rightx;
        //servoUP();
        //SteppermoveRight();
    }
    if(PS3.getButtonPress(LEFT)){ 
    
        Serial.println("Left");
        PS3Val = leftx;
        //servoDOWN();
        //SteppermoveLeft();
    }
    if(PS3.getButtonPress(UP)) 
    {
        Serial.println("UP");
        PS3Val = upx;
        //SteppermoveDown();
        
    }
    if(PS3.getButtonPress(DOWN)) 
    {
        Serial.println("Down");
        PS3Val = downx;
        //SteppermoveUp ();
    }

    //=============================//

    //========== C T C S ==========//
    if(PS3.getButtonPress(CROSS)) 
    {
        Serial.println("Cross");
        PS3Val = crossx;
        servoDOWN();
        
    }
    if(PS3.getButtonPress(TRIANGLE)) 
    {
       Serial.println("Triangle");
       PS3Val = trianglex; 
       servoUP();
    }
    if(PS3.getButtonPress(SQUARE)) 
    {
       PS3Val = squarex;
       Serial.println("Square");
       Serial.println( PS3.getAnalogButton(SQUARE) );
       
       OmegaOfBot = ( -MaxOmegaOfBot / 255 ) * PS3.getAnalogButton(SQUARE);
       Serial.println(OmegaOfBot);
       
       
    }
    if(PS3.getButtonPress(CIRCLE)) 
    {
       PS3Val = circlex;
       Serial.println("Circle");
       Serial.println( PS3.getAnalogButton(CIRCLE) );

       OmegaOfBot = ( MaxOmegaOfBot / 255 ) * PS3.getAnalogButton(CIRCLE);
       Serial.println(OmegaOfBot);
       
       
    }
    //=============================//
    //========== L R ============//

     if(PS3.getButtonPress(L1)) 
    {
       Serial.println("L1");
       PS3Val = l1x;
       Pneumatic2UP();
    }
    if(PS3.getButtonPress(L2)) 
    {
       Serial.println("L2");
       PS3Val = l2x;
       Pneumatic2DOWN();
       
    }
    if(PS3.getButtonPress(L3)) 
    {
       Serial.println("L3");
       PS3Val = l3x;
    }
    
    if(PS3.getButtonPress(R1)) 
    {
       Serial.println("R1");
       PS3Val = r1x;
       Pneumatic1UP();
    }
    if(PS3.getButtonPress(R2)) 
    {
       Serial.println("R2");
       PS3Val = r2x;
       Pneumatic1DOWN();
    }
    if(PS3.getButtonPress(R3)) 
    {
       Serial.println("R3");
       PS3Val = r3x;
    }

    //========== Start Select ==========//
        if(PS3.getButtonPress(START)) 
    {
       Serial.println("Start");
       PS3Val = startx; 
    }
    if(PS3.getButtonPress(SELECT)) 
    {
       Serial.println("Select");
       PS3Val = selectx;
    }
    
    mapping();
}

void mapping()
{
  //=====================================================================//
    //=========================== Mapping =================================//
    
   /* LeftAnalogDataX = PS3.getAnalogHat(LeftHatX) - 127; //Mapping //Shifting Center to 0
    LeftAnalogDataY = 128 - PS3.getAnalogHat(LeftHatY); //Mapping //Shifting Center to 0 // Range (-127 to 128)
    LeftAnalogDataX = LeftAnalogDataX * 2;  // Range(-254 to 256)
    LeftAnalogDataY = LeftAnalogDataY * 2;  // Range(-254 to 256)

    
    if(LeftAnalogDataX > 255) // 256 to 255 range conversion
    {
      LeftAnalogDataX = 255;
    }

    if(LeftAnalogDataY > 255) // 256 to 255 range conversion
    {
      LeftAnalogDataY = 255;
    }
    
    RightAnalogDataX = PS3.getAnalogHat(RightHatX) - 127; //Mapping //Shifting Center to 0 
    RightAnalogDataY = 128 - PS3.getAnalogHat(RightHatY); //Mapping //Shifting Center to 0
    RightAnalogDataX = RightAnalogDataX * 2;  // Range(-254 to 256)
    RightAnalogDataY = RightAnalogDataY * 2;  // Range(-254 to 256)
    
    if(RightAnalogDataX > 255)  // 256 to 255 range conversion
    {
      RightAnalogDataX = 255;
    }

    if(RightAnalogDataY > 255)  // 256 to 255 range conversion
    {
      RightAnalogDataY = 255;
    }*/

    //=====================================================================//
    //=========================== Better way to Map =======================//

    LeftAnalogDataX = PS3.getAnalogHat(LeftHatX);
    LeftAnalogDataY = PS3.getAnalogHat(LeftHatY);
    RightAnalogDataX = PS3.getAnalogHat(RightHatX);
    RightAnalogDataY = PS3.getAnalogHat(RightHatY);

    LeftAnalogDataX = map(LeftAnalogDataX, 0, 255, -255, 255);
    LeftAnalogDataY = map(LeftAnalogDataY, 255, 0, -255, 255);
    RightAnalogDataX = map(RightAnalogDataX, 0, 255, -255, 255);
    RightAnalogDataY = map(RightAnalogDataY, 255, 0, -255, 255);

    /*Serial.print("Lx: ");
    Serial.print(LeftAnalogDataX);
    Serial.print(" Ly: ");
    Serial.print(LeftAnalogDataY);
    Serial.print(" Rx: ");
    Serial.print(RightAnalogDataX);
    Serial.print(" Ry: ");
    Serial.print(RightAnalogDataY);
    Serial.print("\n");*/

    LeftAnalogDataX = LeftAnalogDataX * MaxVx / 255; 
    LeftAnalogDataY = LeftAnalogDataY * MaxVy / 255;
    inverseKine();
}

void inverseKine()
{
    //=================================================================//
    //=================== Inverse Kine ================================//
    
    vel1 = (-sin(theta1) * LeftAnalogDataX) + (cos(theta1) * LeftAnalogDataY) + (OmegaOfBot * RadiusOfBot);
    vel2 = (-sin(theta2) * LeftAnalogDataX) + (cos(theta2) * LeftAnalogDataY) + (OmegaOfBot * RadiusOfBot);
    vel3 = (-sin(theta3) * LeftAnalogDataX) + (cos(theta3) * LeftAnalogDataY) + (OmegaOfBot * RadiusOfBot);

    /*theta1 = theta1 + (OmegaOfBot * dt);
    theta2 = theta2 + (OmegaOfBot * dt);
    theta3 = theta3 + (OmegaOfBot * dt);*/

    //Serial.print(OmegaOfBot);
//    Serial.print(" ");
//    Serial.print(vel1);
//    Serial.print(" ");
//    Serial.print(vel2);
//    Serial.print(" ");
//    Serial.print(vel3);
//    Serial.print("\n");

    /*Serial.print("PWM1: ");
    Serial.print(int((vel1/MaxV1)*255));
    Serial.print(" PWM2: ");
    Serial.print(int((vel2/MaxV1)*255));
    Serial.print(" PWM2: ");
    Serial.print(int((vel3/MaxV1)*255));
    Serial.print("\n");*/
    
    

    if(abs(vel1) >= MaxV1)
    {
      Serial.print("\n V1 Error :");
      Serial.print(String(vel1) + " " + PS3.getAnalogHat(LeftHatX) + " " + PS3.getAnalogHat(LeftHatY) );      
    }
        if(abs(vel2) >= MaxV1)
    {
      Serial.print("\n V2 Error :");
      Serial.print(String(vel2) + " " + PS3.getAnalogHat(LeftHatX) + " " + PS3.getAnalogHat(LeftHatY));  
    }
        if(abs(vel3) >= MaxV1)
    {
      Serial.print("\n V3 Error :");
      Serial.print(String(vel3) + " " + PS3.getAnalogHat(LeftHatX) + " " + PS3.getAnalogHat(LeftHatY) );  
    }
}
