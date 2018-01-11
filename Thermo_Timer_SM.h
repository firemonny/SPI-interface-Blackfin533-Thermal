/*
 * Thermo_Timer_SM.h
 *
 *  Created on: Nov 26, 2017
 *      Author: nschou
 */

#ifndef THERMO_TIMER_SM_H_
#define THERMO_TIMER_SM_H_
#include "blackfin.h"
#include <GPIO2017/ADSP_GPIO_Interface.h>
#include "stdio.h"
#include <uTTCOSg2017/uTTCOSg.h>
#include "CalculateTemp_SM.h"
#define SWITCHBITS_MASK 0x0F00			// Use only PF8 to 11
#define Thermo_MASK 0x0800						// Mask to check  switch 4 is being pressed
#define TimerStatus_MASK 0x0002


extern "C" unsigned short int ASM_Read_Switches_GPIO(void);
void Init_Timer1();
void StoreThermoTimerSM();



#endif /* THERMO_TIMER_SM_H_ */
