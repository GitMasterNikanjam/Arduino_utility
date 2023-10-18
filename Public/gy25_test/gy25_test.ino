// Project: GY-25 test Code (tested in arduino mega2560)

// GY25 is a module that have a mpu6050 sensor and a stm32 microcontroller.
// this module can use for get Euler angle from serial port.
// GY25 serial protocol description in gy25 user manual and it is very simple to 
// communicate with it.

float Roll,Pitch,Yaw;
unsigned char Re_buf[8],counter=0;

void setup()
{ 
Serial.begin(115200);
Serial3.begin(115200); // serial connection with gy25 module.
delay(4000); 
Serial3.write(0XA5); 
Serial3.write(0X54);//correction mode
delay(4000);
Serial3.write(0XA5); 
Serial3.write(0X55);//correction mode
delay(4000);
Serial3.write(0XA5); 
Serial3.write(0X52);//0X51:query mode, return directly to the angle value, to be sent each read, 0X52:Automatic mode,send a direct return angle, only initialization 
}
//looooooooooooooooooop
void loop() {
  t = micros();
  if (Serial3.available()) { 
    serialEvent();
    Serial.print(Roll);
    Serial.print(","); 
    Serial.print(Pitch);
    Serial.print(","); 
    Serial.println(Yaw);
  }
}
//loooooooooooooooooooop END
//data reading function
void serialEvent() { 
 //Serial3.write(0XA5); 
 //Serial3.write(0X51);//send it for each read
 while (Serial3.available()) { 
 Re_buf[counter]=(unsigned char)Serial3.read();
 if(counter==0&&Re_buf[0]!=0xAA) return; 
 counter++; 
 if(counter==8) { // package is complete 
 counter=0; 
 if(Re_buf[0]==0xAA && Re_buf[7]==0x55) { // data package is correct 
 Yaw=(int16_t)(Re_buf[1]<<8|Re_buf[2])/100.00; 
 Pitch=(int16_t)(Re_buf[3]<<8|Re_buf[4])/100.00;
 Roll=(int16_t)(Re_buf[5]<<8|Re_buf[6])/100.00;
 } 
 } 
 } 
}
