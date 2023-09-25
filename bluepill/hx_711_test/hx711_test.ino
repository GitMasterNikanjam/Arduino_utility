// Project: HX711_ADC test on bluepill

// Any digital IO of bluepill can set for DOUT and SCK pin.
// Its very simple to use this library for bluepill. same as other standard arduino boards.


#include "HX711_ADC.h"

#define DOUT_PIN PB0
#define SCK_PIN PB1

HX711_ADC loadcell_1(DOUT_PIN, SCK_PIN);
float weight;

void setup() {
  Serial.begin(9600);
  loadcell_1.begin();
  loadcell_1.start(1000,true);
  loadcell_1.setSamplesInUse(1);
}

void loop() {
  
  if(loadcell_1.update())                              //if conversion is ready; read out 24 bit data and add to dataset
    weight = loadcell_1.getData()/254.0;   
    
    Serial.println(weight);
    delay(10);
    
}
