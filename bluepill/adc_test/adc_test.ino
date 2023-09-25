// Project: ADC test

//  The BluePill development board, which is based on the STM32 microcontroller,
//  has multiple pins that you can use for reading analog values through the built-in ADC (Analog-to-Digital Converter).
//  Here are some of the commonly used pins for ADC on the BluePill board:
//  PA0 (Pin 1): This is the most commonly used analog input pin for ADC.
//  It is labeled as "ADC_IN0" and corresponds to Analog Channel 0 (ADC1_IN0).
//  
//  PA1 (Pin 2): This pin is labeled as "ADC_IN1" and corresponds to Analog Channel 1 (ADC1_IN1).
//  PA2 (Pin 3): Labeled as "ADC_IN2," it corresponds to Analog Channel 2 (ADC1_IN2).
//  PA3 (Pin 4): Labeled as "ADC_IN3," it corresponds to Analog Channel 3 (ADC1_IN3).
//  PA4 (Pin 5): Labeled as "ADC_IN4," it corresponds to Analog Channel 4 (ADC1_IN4).
//  PA5 (Pin 6): Labeled as "ADC_IN5," it corresponds to Analog Channel 5 (ADC1_IN5).
//  PA6 (Pin 7): Labeled as "ADC_IN6," it corresponds to Analog Channel 6 (ADC1_IN6).
//  PA7 (Pin 8): Labeled as "ADC_IN7," it corresponds to Analog Channel 7 (ADC1_IN7).
//  PB0 (Pin 9): Labeled as "ADC_IN8," it corresponds to Analog Channel 8 (ADC1_IN8).
//  PB1 (Pin 10): Labeled as "ADC_IN9," it corresponds to Analog Channel 9 (ADC1_IN9).

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);
}

void loop() {
  // Read from ADC on pin PA0 (analog pin 0)
  int adcValue = analogRead(PB1);

  // Print the ADC value to the serial monitor
  Serial.println(adcValue);

  // Add a delay before the next reading
  delay(1000);
}
