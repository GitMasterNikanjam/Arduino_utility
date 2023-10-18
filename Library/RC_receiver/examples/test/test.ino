#include "RC_Receiver.h"
#include <Servo.h>
Servo myservo;  // create servo object to control a servo


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
delay(1000);
RC.ch_pinchange_attach(1,5);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
myservo.writeMicroseconds(1500); 
RC.calibration_start();
}

void loop() {
  // put your main code here, to run repeatedly:
uint16_t i=RC.get_chm_value(1);
Serial.println(i);
delay(1000);
}
