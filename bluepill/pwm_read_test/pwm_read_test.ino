// Project: pwm read on bluepill

// there are two way of read pwm. 1: use external interrupt. 2: us pulsein function.
// use external interrupts for read pwm pulses is very accurate and effecient than use pulsin function.

// in bluepill 
#include <Servo.h>

Servo myservo;

#define   myservo_pin   PA0
#define   pwm_read_pin1  PB12
#define   pwm_read_pin2  PA2

uint32_t t_pwm_read_last;
uint16_t pwm_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(pwm_read_pin1, INPUT_PULLDOWN);
  pinMode(pwm_read_pin2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pwm_read_pin1), pwm_read_cal, CHANGE);
  myservo.attach(myservo_pin, 1000, 2000);
  myservo.writeMicroseconds(1600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("pwm_read interrupt value: ");
  Serial.println(pwm_value);                    // Recommended way to read pwm is use external interrupts
  Serial.print("pwm_read pulsein value: ");
  Serial.println(pulseIn(pwm_read_pin2, HIGH)); // this way of read pwm is less accurate.
  delay(1000);
}

void pwm_read_cal(void)
{
  if(digitalRead(pwm_read_pin1) == HIGH)
  {
    t_pwm_read_last = micros();
  }
  else
  {
    pwm_value = micros() - t_pwm_read_last;
  }
}
