/*
 * Thermo_Timer_SM.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: nschou
 */
#include "Thermo_Timer_SM.h"


enum thermo_timer_SM {WAITING_STATE, WRITING_STATE};
// The function is to inital timer 1;
volatile unsigned int timer1_width;
volatile unsigned int timer1_period;
volatile int counter_store = 0;
volatile bool calculate_signal = false;
extern unsigned long int FirstBufferT1[10];
extern unsigned long int SecondBufferT1[10];
extern unsigned long int FirstBufferT2[10];
extern unsigned long int SecondBufferT2[10];

void Init_Timer1()
{
	//*pIMASK =	0x0000001F;
	//*pSIC_IMASK =0x00000000;
	//SET the timer 1 to be WDTH_CAP mode
	*pTIMER1_CONFIG=0x021E;  //
	//TIMER ENABLE
	*pTIMER_ENABLE= 0x0002;
	*pTIMER_STATUS = 0x0002;
}
void StoreThermoTimerSM(){
	static thermo_timer_SM next_thermo_command= WAITING_STATE;
	unsigned short int allGPIOBits =  ASM_Read_Switches_GPIO( );
	unsigned short int switchBits =  allGPIOBits & SWITCHBITS_MASK;

	switch (next_thermo_command)
	{
		case(WAITING_STATE):
				if(*pTIMER_STATUS&0x0002)
				{
					next_thermo_command = WRITING_STATE;
				} //reset timer1 W1C

				break;

		case(WRITING_STATE):
			//if timer 1 is ready use it.

				timer1_width = *pTIMER1_WIDTH;
				timer1_period = *pTIMER1_PERIOD;
				unsigned long int *pT1;
				unsigned long int *pT2;
				float* ptemp;
				if(counter_store<10)
				{
				pT1 = FirstBufferT1;
				pT2 = FirstBufferT2;
				pT1[counter_store]=timer1_width;
				pT2[counter_store]=timer1_period-timer1_width;
				counter_store++;
				}
				else
				{
				unsigned temp_counter = counter_store -10;
				pT1 = SecondBufferT1;
				pT2 = SecondBufferT2;
				pT1[temp_counter]=timer1_width;
				pT2[temp_counter]=timer1_period-timer1_width;
				counter_store++;

				}
				if(counter_store==10)
				{
					uTTCOSg_AddThread(CalculateTemp_SM, NO_DELAY, RUN_ONCE);
				}
				else if (counter_store>=20)
				{
					uTTCOSg_AddThread(CalculateTemp_SM, NO_DELAY, RUN_ONCE);
					counter_store =0;
				}
				*pTIMER_STATUS = 0x0002; // W1C
				next_thermo_command = WAITING_STATE;
			break;

	}
}
