/*
 * DisplayLED_SM.h
 *
 *  Created on: Nov 28, 2017
 *      Author: nschou
 */

#ifndef DISPLAYLED_SM_H_
#define DISPLAYLED_SM_H_

#include "blackfin.h"
#include <GPIO2017/ADSP_GPIO_Interface.h>
#include "stdio.h"



#define SWITCHBITS_MASK 0x0F00			// Use only PF8 to 11
#define SW1_MASK 0x0100						// Mask to check switch 1 is being pressed
#define LED2_MASK 0x02
#define LED3_MASK 0x04
#define LED4_MASK 0x08
#define LEDBITS unsigned char
#define LED2_4mask 0xf5


extern "C" unsigned short int ASM_Read_Switches_GPIO(void);
void DisplayLED_SM();
void Flash_LED2(void);
void Flash_LED4(void);
#endif /* DISPLAYLED_SM_H_ */
