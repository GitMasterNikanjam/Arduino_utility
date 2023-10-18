/*
RC_Receiver - a small RC hobby receiver library for Arduino.
Copyright (C) 2022 Mohammad Nikanjam
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

*/

#include "RC_Receiver.h"

RC_Receiver RC;

void RC_Receiver::ch_attach(uint8_t channel_number, uint8_t pin_number)
{
	if((channel_number>8)||(channel_number<1))
	  {
		Serial.println("Warning!,RC channel_number must be intiger at domain:[1,8]");
		Serial.print("Channel number:");
		Serial.print(channel_number);
		Serial.println(" Can not Created");
	  }
	else
	{
		pinMode(pin_number,INPUT_PULLUP);
		RC.channel_pin[channel_number-1]=pin_number;

		switch(channel_number)
		{
		case 1:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH1, CHANGE);
		break;
		case 2:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH2, CHANGE);
		break;
		case 3:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH3, CHANGE);
		break;
		case 4:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH4, CHANGE);
		break;
		case 5:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH5, CHANGE);
		break;
		case 6:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH6, CHANGE);
		break;
		case 7:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH7, CHANGE);
		break;
		case 8:
			attachInterrupt(digitalPinToInterrupt(pin_number), calcInput_CH8, CHANGE);
		break;		
		}
	}
}

void RC_Receiver::ch_pinchange_attach(uint8_t channel_number, uint8_t pin_number)
{
	if((channel_number>8)||(channel_number<1))
	  {
		Serial.println("Warning!,RC channel_number must be intiger at domain:[1,8]");
		Serial.print("Channel number:");
		Serial.print(channel_number);
		Serial.println(" Can not Created");
	  }
	else
	{
		pinMode(pin_number,INPUT_PULLUP);
		RC.channel_pin[channel_number-1]=pin_number;

		switch(channel_number)
		{
		case 1:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH1, CHANGE);
		break;
		case 2:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH2, CHANGE);
		break;
		case 3:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH3, CHANGE);
		break;
		case 4:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH4, CHANGE);
		break;
		case 5:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH5, CHANGE);
		break;
		case 6:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH6, CHANGE);
		break;
		case 7:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH7, CHANGE);
		break;
		case 8:
			attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pin_number), calcInput_CH8, CHANGE);
		break;		
		}
	}
}

uint16_t RC_Receiver::get_ch_value(uint8_t channel_number)
{
	return RC.ch_value[channel_number-1];
}

uint16_t RC_Receiver::get_chm_value(uint8_t channel_number)
{
	return RC.chm_value[channel_number-1];
}

uint16_t RC_Receiver::get_chmf_value(uint8_t channel_number)
{
	return RC.chmf_value[channel_number-1];
}

uint16_t RC_Receiver::ch_map(uint8_t channel_number)
{
	return map(RC.ch_value[channel_number-1],RC.ch_min[channel_number-1],RC.ch_max[channel_number-1],RC.PWM_MAP_MIN,RC.PWM_MAP_MAX);
}
	
void RC_Receiver::set_map_domain(uint16_t min, uint16_t max)
{
	RC.PWM_MAP_MIN=min;
	RC.PWM_MAP_MAX=max;
}

void RC_Receiver::set_rpy_deadzone(uint16_t deadzone)
{
	RC.RPY_DEADZONE=deadzone;	
}

void RC_Receiver::set_ch_domain(uint8_t channel_number, uint16_t min, uint16_t max)
{

RC.ch_min[channel_number-1]= min;
RC.ch_max[channel_number-1]= max;
RC.ch_mid[channel_number-1]=(min+max/2.0);
		
}

void RC_Receiver::set_filter_frq(float frq)
{
	RC.FILTER_FRQ=frq;
	RC.alpha_flt=1.0/(1.0+2*3.1415*RC.FILTER_FRQ/RC.UPDATE_FRQ);
}

void RC_Receiver::set_update_frq(float frq)
{
	RC.UPDATE_FRQ=frq;
	RC.alpha_flt=1.0/(1.0+2*3.1415*RC.FILTER_FRQ/RC.UPDATE_FRQ);
}

void RC_Receiver::calibration_start(void)
{
	RC.calibration_flag=true;	
}

void RC_Receiver::calibration_stop(void)
{
	RC.calibration_flag=false;	
}
	
void RC_Receiver::update_value(void)
{
	uint32_t t=millis();
	
	if((t-RC.T_last_update)>=(1000.0/RC.UPDATE_FRQ))
	{
		uint16_t chmf_value_last;
		
		for(int i=1;i<=8;i++)
		{
			chm_value[i-1]=RC.ch_map(i);
			chmf_value_last=chmf_value[i-1];		
			chmf_value[i-1]=RC.alpha_flt*chmf_value[i-1]+(1.0-RC.alpha_flt)*chm_value[i-1];
			if(RC.calibration_flag)
			{
				if(chmf_value[i-1]>chmf_value_last)
				RC.ch_max[i-1]=chmf_value[i-1];
				else
				RC.ch_min[i-1]=chmf_value[i-1];
			}
		}	
		
		RC.T_last_update=t;
	}
}	
	
RC_Receiver::RC_Receiver(void)
{
		// Set default value at construction function:
		
		RC.PWM_MAP_MIN=1000.0,RC.PWM_MAP_MAX=2000.0;					// min and max vlaue for map value of ch [us]
		RC.RPY_DEADZONE=0;												// deadzone for (roll/pitch/yaw)/(ch1/ch2/ch4)
		RC.FILTER_FRQ=10.0;
		RC.UPDATE_FRQ=100;
		RC.alpha_flt=1.0/(1.0+2*3.1415*RC.FILTER_FRQ/RC.UPDATE_FRQ);
	}
// ###########################################################################################################
// rc interrupts fuctions :

 void calcInput_CH1(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[0]) == HIGH)
  { 
    RC.start_period[0] = micros();
  }
  else
  {
      RC.ch_value[0] = (int)(micros() - RC.start_period[0]);
      RC.start_period[0] = 0;
  }
}

 void calcInput_CH2(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[1]) == HIGH)
  { 
    RC.start_period[1] = micros();
  }
  else
  {
      RC.ch_value[1] = (int)(micros() - RC.start_period[1]);
      RC.start_period[1] = 0;
  }
}

 void calcInput_CH3(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[2]) == HIGH)
  { 
    RC.start_period[2] = micros();
  }
  else
  {
      RC.ch_value[2] = (int)(micros() - RC.start_period[2]);
      RC.start_period[2] = 0;
  }
}

 void calcInput_CH4(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[3]) == HIGH)
  { 
    RC.start_period[3] = micros();
  }
  else
  {
      RC.ch_value[3] = (int)(micros() - RC.start_period[3]);
      RC.start_period[3] = 0;
  }
}

 void calcInput_CH5(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[4]) == HIGH)
  { 
    RC.start_period[4] = micros();
  }
  else
  {
      RC.ch_value[4] = (int)(micros() - RC.start_period[4]);
      RC.start_period[4] = 0;
  }
}

 void calcInput_CH6(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[5]) == HIGH)
  { 
    RC.start_period[5] = micros();
  }
  else
  {
      RC.ch_value[5] = (int)(micros() - RC.start_period[5]);
      RC.start_period[5] = 0;
  }
}

 void calcInput_CH7(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[6]) == HIGH)
  { 
    RC.start_period[6] = micros();
  }
  else
  {
      RC.ch_value[6] = (int)(micros() - RC.start_period[6]);
      RC.start_period[6] = 0;
  }
}

 void calcInput_CH8(void)
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(RC.channel_pin[7]) == HIGH)
  { 
    RC.start_period[7] = micros();
  }
  else
  {
      RC.ch_value[7] = (int)(micros() - RC.start_period[7]);
      RC.start_period[7] = 0;
  }
}

