/*
RC_Receiver - a small RC hobby receiver library for Arduino.
Copyright (C) 2022 Mohammad Nikanjam
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library use Hardware and Software interrupts of arduino boards.
use Hardware interrupts pins for HIGH precision get value of RC channel pin.
use Software interrupts pins for LOW precision get value of RC channel pin.

This Library use extra library PinChangeInterrupt Library 1.2.9.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

*/

/*
Types of Interrupts  
There are two types of interrupts:

Hardware Interrupt: It happens when an external event occurs like an external interrupt pin changes its state from 
LOW to HIGH or HIGH to LOW.
These interrupt are interpreted by hardware and are very fast. These interrupts can be set to trigger on the event 
of RISING or FALLING or LOW levels.

Software Interrupt: It happens according to the instruction from the software. For example Timer interrupts are software interrupt.
Arduinos can have more interrupt pins enabled by using pin change interrupts.
The library for use software interrupts is PinChangeInterrupt Library 1.2.9. That it can install from Manage Libraries Tab in Arduino IDE Tab.
*/

/*
Arduino Board External Interrupt pins:(Hardware interrupt pins)

UNO , NANO
2,3

Mega
2,3,18,19,20,21(pins 20 & 21 are not available to use for interrupts while they are used for I2C communication)

Nano 33 IoT
2, 3, 9, 10, 11, 13, A1, A5, A7

Due
all digital pins
*/

/*
PinChangeInterrupt Library 1.2.9:

PinChangeInterrupt library with a resource friendly implementation (API and LowLevel).
PinChangeInterrupts are different than normal Interrupts. See detail below.

Supported pins for PinChangeInterrupt:

Arduino Uno/Nano/Mini: All pins are usable
Arduino Mega: 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64),
           A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
Arduino Leonardo/Micro: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI)
HoodLoader2: All (broken out 1-7) pins are usable
Attiny24/44/84: All pins are usable
Attiny25/45/85: All pins are usable
Attiny13: All pins are usable
Attiny441/841: All pins are usable
Attiny261/461/861: All pins are usable
Attiny2313/2313A/4313: PORTB is usable
ATmega644/ATmega644P/ATmega1284P: All pins are usable
ATmega162: PORTA and PORTC usable
ATmega48/88/168/328/328PB: All pins are usable

*/

#ifndef RC_Receiver_h
#define RC_Receiver_h

#include "Arduino.h"

#include <PinChangeInterrupt.h>				//PinChangeInterrupt Library 1.2.9 to up
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define _RC_RECEIVER_VERSION 1 // software version of this library


class RC_Receiver
{
public:

	uint16_t ch_value[8],chm_value[8],chmf_value[8];				// raw value, map value,filter value of ch. [us] 
	uint8_t channel_pin[8];											// digital pin number of arduino that has hardware interrupt.
	volatile unsigned long start_period[8];							// Start timer value.
	
	RC_Receiver(void);
	
	void ch_attach(uint8_t channel_number, uint8_t pin_number);
	void ch_pinchange_attach(uint8_t channel_number, uint8_t pin_number);
	
	uint16_t get_ch_value(uint8_t channel_number);
	uint16_t get_chm_value(uint8_t channel_number);
	uint16_t get_chmf_value(uint8_t channel_number);
	
	uint16_t ch_map(uint8_t channel_number);
	
	void set_map_domain(uint16_t, uint16_t);
	void set_rpy_deadzone(uint16_t);
	void set_ch_domain(uint8_t channel_number, uint16_t min, uint16_t max);
	void set_filter_frq(float);
	void set_update_frq(float);
	
	void calibration_start(void);
	void calibration_stop(void);

	void update_value(void);

private:

	uint16_t PWM_MAP_MIN,PWM_MAP_MAX;								// min and max vlaue for map value of ch [us]
	uint16_t RPY_DEADZONE;											// deadzone for (roll/pitch/yaw)/(ch1/ch2/ch4)
	float FILTER_FRQ;
	float UPDATE_FRQ;
	float alpha_flt;
	volatile unsigned long T_last_update;
	uint16_t ch_min[8]={1000,1000,1000,1000,1000,1000,1000,1000};	// min domain of ch. default=1000 us
	uint16_t ch_mid[8]={1500,1500,1500,1500,1500,1500,1500,1500};	// mid domain of ch. default=1500 us
	uint16_t ch_max[8]={2000,2000,2000,2000,2000,2000,2000,2000};	// max domain of ch. default=2000 us
	
	bool calibration_flag=false;
	
};

 void calcInput_CH1(void);
 void calcInput_CH2(void);
 void calcInput_CH3(void);
 void calcInput_CH4(void);
 void calcInput_CH5(void);
 void calcInput_CH6(void);
 void calcInput_CH7(void);
 void calcInput_CH8(void);
 
 extern RC_Receiver RC;
 
#endif
