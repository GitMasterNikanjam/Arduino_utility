// Project: LCD charechter test for bluepill.

// AT this project we use 4 pin data way to communicate with lcd charechter.
// include LCD library code
#include <LiquidCrystal.h>  // is compatible with bluepill board. 

// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(PA0, PA1, PA2, PA3, PA4, PA5);

void setup() {

  // initialize the LCD screen with 16 column & 2 rows
  // in case of 20x4 LCD use: lcd.begin(20, 4);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);           // move cursor to position (0, 0) -- 1st column & 1st row
  lcd.print("STM32 BLUE PILL");  // print text on the LCD
  lcd.setCursor(0, 1);           // move cursor to position (0, 1) -- 1st column & 2nd row
  lcd.print("LCD Example");      // print text on the LCD
  
  delay(5000);    // wait 5 seconds
  lcd.clear();    // clear the display
  lcd.setCursor(0, 0);            // move cursor to position (0, 0) -- 1st column & 1st row
  lcd.print("Hello world!");      // print text on the LCD

}

void loop() {

  lcd.setCursor(0, 1);            // move cursor to position (0, 1) -- 1st column & 2nd row
  uint32_t n = millis() / 1000;   // use millis() function to get number of seconds since power up
  lcd.print( n );                 // print the variable 'n' on the LCD
  delay(1000);                    // wait a second

}

// end of code.
