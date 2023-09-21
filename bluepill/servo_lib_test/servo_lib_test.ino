// Project: Servo library test for bluepill board.

// bluepill has some hardware pin for generation of pwm signal: (PA0,PA1,PA2,PA3,PA6,PA7,PA8,PA9,PA10,PB1,PB6,PB7,PB8,PB9,PB0)
// Hint: other pin of bluepill can not generate hardware pwm and can not software pwm even use servo lib.

#include <Servo.h>

Servo myservo;

#define   myservo_pin   PA0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         // USB port serial
  pinMode(PA1,INPUT_PULLDOWN);
  myservo.attach(myservo_pin, 1000, 2000);
  myservo.writeMicroseconds(1600);
 }

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t u = pulseIn(PA1, HIGH);
  Serial.println(u);
  delay(1000);
}
