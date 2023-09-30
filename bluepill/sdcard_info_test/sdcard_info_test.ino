// Project: SDCARD test for bluepill. get information of sdcard.

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
 
void printDirectory(File dir, int numTabs);
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
 
  Serial.print("\nInitializing SD card...");
 
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
 
  uint32_t cardSize = SD.card()->sectorCount();
 
  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (SD.card()->type()) {
  case SD_CARD_TYPE_SD1:
    Serial.println(F("SD1"));
    break;
  case SD_CARD_TYPE_SD2:
    Serial.println(F("SD2"));
    break;
 
  case SD_CARD_TYPE_SDHC:
    if (cardSize < 70000000) {
      Serial.println(F("SDHC"));
    } else {
      Serial.println(F("SDXC"));
    }
    break;
 
  default:
    Serial.println(F("Unknown"));
  }
 
 
//  print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(int(SD.vol()->fatType()), DEC);
 
  Serial.print("Card size:  ");
  Serial.println((float) 0.000512*cardSize);
 
  Serial.print("Total bytes: ");
  Serial.println(0.000512*SD.vol()->clusterCount()*SD.sectorsPerCluster());
 
  Serial.print("Free bytes: ");
  Serial.println(0.000512*SD.vol()->freeClusterCount()*SD.sectorsPerCluster());
 
  File dir =  SD.open("/");
  printDirectory(dir, 0);
 
}
 
void loop(void) {
}
 
void printDirectory(File dir, int numTabs) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    entry.printName(&Serial);
 
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      uint16_t pdate;
      uint16_t ptime;
      entry.getModifyDateTime(&pdate, &ptime);
      char c[50];
      sprintf(c,"\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", FS_YEAR(pdate), FS_MONTH(pdate), FS_DAY(pdate), FS_HOUR(ptime), FS_MINUTE(ptime), FS_SECOND(ptime));
      Serial.print(c);
    }
    entry.close();
  }
}
