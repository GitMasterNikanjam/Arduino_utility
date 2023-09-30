// Project: SDCARD test for bluepill. read and write in sdcard.

// SdFat library is essential for bluepill and can not use sd standard library for it
// For use SdFat library should connect sdcard to spi port of bluepill.

// Default SPI pins for bluepill are:
// SPI1(NSS,SCK,MISO,MOSO) : (PA4,PA5,PA6,PA7)
// SPI2(NSS,SCK,MISO,MOSI) : (PB12,PB13,PB14,PB15)

// NSS pin can be any digital pin.

#include <SPI.h>
#include "SdFat.h"
 
#define SD_CS_PIN PA4
 
SdFat SD;
 
 
File myFile;
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
 
  Serial.print("Initializing SD card...");
 
  if (!SD.begin(SD_CS_PIN)) {
      Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
 
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
 
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop() {
  // nothing happens after setup
}
