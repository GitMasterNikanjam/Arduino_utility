// Project: pwm read on bluepill

// there are two way of read pwm. 1: use external interrupt. 2: us pulsein function.
// use external interrupts for read pwm pulses is very accurate and effecient than use pulsin function.

// external interrupts pin can use on bluepill is bellow:
//  EXTI0: PA0
//  EXTI1: PA1
//  EXTI2: PA2
//  EXTI3: PA3
//  EXTI4: PA4
//  EXTI5: PA5, PB5
//  EXTI6: PA6, PB6
//  EXTI7: PA7, PB7
//  EXTI8: PA8, PB8
//  EXTI9: PA9, PB9
//  EXTI10: PA10, PB10
//  EXTI11: PA11, PB11
//  EXTI12: PA12, PB12
//  EXTI13: PA13, PB13
//  EXTI14: PA14, PB14
//  EXTI15: PA15, PB15

//  EXTI lines are a limited resource on the microcontroller,
//  and each EXTI line can typically be associated with multiple pins that share the same line. 
//  In the case of EXTI14, both PA14 and PB14 share the same EXTI line,
//  so you have to choose one or the other to use as an external interrupt source.
//  
//  If you need to use multiple external interrupts simultaneously,
//  you will need to choose pins that are associated with different EXTI lines.
//  You can refer to the list of EXTI lines and their corresponding pins in the previous response
//  to see which combinations are available for your specific use case.


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
