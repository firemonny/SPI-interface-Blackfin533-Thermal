/*
 * DisplayLED_SM.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: nschou
 */

#include "stdio.h"

#include "DisplayLED_SM.h"


enum DisplayLED_State {BIOSENSOR_STATE, ACTUALTEMP_STATE};
enum LED2_STATE {LED2_SUPPOSED_TO_BE_OFF, LED2_SUPPOSED_TO_BE_ON};
enum LED4_STATE {LED4_SUPPOSED_TO_BE_OFF, LED4_SUPPOSED_TO_BE_ON};
enum Temperture_State {HIGHER,SAME,LOWER};


extern float current_Temperture;
extern float past_Temperature;
extern int current_Temperture_int;
extern int past_Temperature_int;

void DisplayLED_SM(){
	static DisplayLED_State nextLEDstate = BIOSENSOR_STATE;
	static Temperture_State current_temp_state = LOWER;

	past_Temperature_int = past_Temperature;
	current_Temperture_int = current_Temperture;
// Read Switches
	unsigned short int allGPIOBits =  ASM_Read_Switches_GPIO( );
	unsigned short int switchBits =  allGPIOBits & SWITCHBITS_MASK;

//Read LED bits
	unsigned char currentLEDvalue = Read_LED_GPIOInterface();
	currentLEDvalue = currentLEDvalue & 0xFE;

	switch(nextLEDstate)
	{
	LEDBITS templed;
		case(BIOSENSOR_STATE):

			// Write LED1 to LED Display
			templed = currentLEDvalue &0xf0;
			Write_LED_GPIOInterface(templed);
			// if SW1 equals 1, go to ACTUALTEMP_STATE
			if ((switchBits & SW1_MASK) == SW1_MASK)
			{
				nextLEDstate = ACTUALTEMP_STATE;
			}
			break;

		case(ACTUALTEMP_STATE):

			// if SW1 equals 0, go to ACTUALTEMP_STATE
			templed = currentLEDvalue | 0x01;
				Write_LED_GPIOInterface(templed);// Compare current temperature with previous temperature
			if ((switchBits & SW1_MASK)  != SW1_MASK)
			{

				nextLEDstate = BIOSENSOR_STATE;
			}
			else
			{
				if(current_Temperture_int > past_Temperature_int){
				current_temp_state = HIGHER;
					}
				else if(current_Temperture_int == past_Temperature_int){
				current_temp_state = SAME;
					}
				else{
				current_temp_state=LOWER;
					}
		templed = Read_LED_GPIOInterface();
		templed |= LED3_MASK;
		Write_LED_GPIOInterface(templed);
		switch(current_temp_state)
				{
				// in actual temperture mode LED3 should Light up
			case(LOWER):
				if(current_temp_state!=LOWER)
					{
						LEDBITS tempLED = Read_LED_GPIOInterface();
						tempLED &= LED2_4mask;
						Write_LED_GPIOInterface(tempLED);
					}
				else Flash_LED4();
				break;
			case(SAME):

				LEDBITS tempLED = Read_LED_GPIOInterface();
				tempLED &= LED2_4mask;
				Write_LED_GPIOInterface(tempLED);

			break;
			case(HIGHER):
				if(current_temp_state!=HIGHER)
						{
							LEDBITS tempLED = Read_LED_GPIOInterface();
							tempLED &= LED2_4mask;
							Write_LED_GPIOInterface(tempLED);
						}
				else Flash_LED2();
				break;

				}

			}
			break;
	}

}
// Flash LED2
void Flash_LED2(void){
	static LED2_STATE nextTime = LED2_SUPPOSED_TO_BE_ON;
	LEDBITS currentLEDvalue = Read_LED_GPIOInterface();
	LEDBITS newLEDvalue = currentLEDvalue;
	switch (nextTime) {
	case LED2_SUPPOSED_TO_BE_OFF:
	  newLEDvalue = newLEDvalue & ~LED2_MASK;
	  nextTime = LED2_SUPPOSED_TO_BE_ON;
	  break;
	case LED2_SUPPOSED_TO_BE_ON:
	  newLEDvalue = newLEDvalue | LED2_MASK;
	  nextTime = LED2_SUPPOSED_TO_BE_OFF;
	  break;
	default:
	  printf("Should never get here in FlashLED2\n");
	}
	Write_LED_GPIOInterface(newLEDvalue);
}
void Flash_LED4(void){
	static LED4_STATE nextTime = LED4_SUPPOSED_TO_BE_ON;
	LEDBITS currentLEDvalue = Read_LED_GPIOInterface();
	LEDBITS newLEDvalue = currentLEDvalue;
	switch (nextTime) {
	case LED4_SUPPOSED_TO_BE_OFF:
	  newLEDvalue = newLEDvalue & ~LED4_MASK;
	  nextTime = LED4_SUPPOSED_TO_BE_ON;
	  break;
	case LED4_SUPPOSED_TO_BE_ON:
	  newLEDvalue = newLEDvalue | LED4_MASK;
	  nextTime = LED4_SUPPOSED_TO_BE_OFF;
	  break;
	default:
	  printf("Should never get here in FlashLED4\n");
	}
	Write_LED_GPIOInterface(newLEDvalue);
}
// Flash LED4
