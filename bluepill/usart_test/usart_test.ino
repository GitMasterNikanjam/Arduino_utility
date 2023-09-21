// Project title: Test USART1/2/3 bluepill

// BluePill default pins for USART:
// USART1 pin(TX1,RX1):(PA9,PA10)
// USART1 pin(TX1,RX1):(PA2,PA3)
// USART1 pin(TX1,RX1):(PB10,PB11)
// Hint: If you use arduino bootloader on bluepill, dont use usb pin(PA11,PA12) for other purpose.

void setup() {

 Serial.begin(9600); // for USB (if active on arduino bootloader)
 Serial1.begin(9600); // for USART 1
 Serial2.begin(9600); // for USART 2
 Serial3.begin(9600); // for USART 3
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Serial USB!");
  delay(1000);
  Serial1.println("Serial 1!");
  delay(1000);
  Serial2.println("Serial 2!");
  delay(1000);
  Serial3.println("Serial 3!");
  delay(1000);

}
