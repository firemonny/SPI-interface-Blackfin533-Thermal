/*
 * SwitchesToLEDs_SM.cpp
 *
 *  Created on: Oct 7, 2017
 *      Author: nschou
 */
#include "SwitchesToLEDs_SM.h"
#include <GPIO2017/ADSP_GPIO_Interface.h>
#include "stdio.h"

#define DRIVECAR_STATEMACHNE true
#define SWITCHESTOLEDs_SM_ON true

extern "C" unsigned short int ASM_Read_Switches_GPIO(void);
//Car status definition from pre-lab
//enum RECIEVE_SIGNAL_STATE {GETTING_CAR_COMMAND, STORE_CAR_COMMAND};  //Monny add
enum GETTING_CAR_COMMAD_SM {STATE_RELEASE, STATE_RISING,STATE_PRESS, STATE_FALLING};
//Global variable declartion
static unsigned short int SW4timer=0;
static unsigned char CarCommand[11];
static unsigned short int CarcommandNum=0;
static bool ValidCarCommand = false;
static unsigned short int state =0;
static unsigned short int counterSW4Presstimer=0;

#if DRIVECAR_STATEMACHNE
#define COAST_NOPOWER 0x00
#define TURN_RIGHT 0x01
#define CAR_FORWARD 0x02
#define TURN_LEFT 0x04
#define CAR_BACKWARD 0x08
#define STOP 0xff									//Monny add
#define CAR_FORWARD_LEFT (CAR_FORWARD | TURN_LEFT)
#define CAR_FORWARD_RIGHT (CAR_FORWARD | TURN_RIGHT)
#define CAR_BACKWARD_LEFT (CAR_BACKWARD | TURN_LEFT)
#define CAR_BACKWARD_RIGHT (CAR_BACKWARD | TURN_RIGHT)
#define ERROR_SIGNAL 7

void DriveCar_StateMachine1(void){
	extern volatile bool Secondloop;
	extern volatile bool Firstloop;
	if(state<CarcommandNum)
	{
		unsigned char currentLEDvalue = Read_LED_GPIOInterface();
		currentLEDvalue = currentLEDvalue & 0xF0;
		unsigned char LEDBits =  currentLEDvalue | CarCommand[state];
		Write_LED_GPIOInterface(LEDBits);
		state++;
	}
	else
	{
	unsigned char currentLEDvalue = Read_LED_GPIOInterface();
	currentLEDvalue = currentLEDvalue & 0xF0;
	unsigned char LEDBits =  currentLEDvalue | CarCommand[state];
	Write_LED_GPIOInterface(LEDBits);
	state =0;
	CarcommandNum = 0;
	Secondloop = false;
	Firstloop = true;
	}
	}
#endif
#if SWITCHESTOLEDs_SM_ON
void SwitchesToLEDs_SM(void) {
// Assume LED and switch interface already on
	/*Message for David
	 *The extern volatile bool  TARD_OS_loop1_quit is declared in global.
	 *The The declaration will cause double declaration
	 */
	extern volatile bool Firstloop;
     unsigned short int allGPIOBits =  ASM_Read_Switches_GPIO( );
     unsigned short int switchBits =  allGPIOBits & SWITCHBITS_MASK;
     /* message for David The origin code will not work
      * unsigned char LEDBits = (switchBits >> 8) | switchBits;
      * Reason1: Because It will overwrite the LED and put the wrong LED pattern into the GPIO
    	Reason2: I add the mask for the LED bits, becaue The LED will not gone.
     */
     unsigned char currentLEDvalue = Read_LED_GPIOInterface();
     currentLEDvalue = currentLEDvalue & 0xF0;
     unsigned char LEDBits = (switchBits >> 8) | currentLEDvalue;
     Write_LED_GPIOInterface(LEDBits);

     // Demonstrate making loop quit if SW4 pressed
	// if ((switchBits & SW4_MASK) == SW4_MASK) Firstloop = false;
}
#endif
//Function got GetCarCommand (SW4 control function)

void GetCarCommand_SM(void)
{
	static GETTING_CAR_COMMAD_SM next_Car_command= STATE_RELEASE;
	unsigned short int allGPIOBits =  ASM_Read_Switches_GPIO( );
	unsigned short int switchBits =  allGPIOBits & SWITCHBITS_MASK;
	switch (next_Car_command)
	{
	case(STATE_RELEASE):

		if((switchBits & SW4_MASK) == SW4_MASK)
			{
				next_Car_command= STATE_RISING;
			//	printf("STATE_RISING\n");
			}

		break;
	case(STATE_RISING):
		next_Car_command = STATE_PRESS;
		break;
	case(STATE_PRESS):
	{

		if((switchBits & SW4_MASK) != SW4_MASK)
				{
					next_Car_command=STATE_FALLING;
				//	printf("STATE_FALLING\n");
				}
		SW4timer++;
		break;
	}
	case(STATE_FALLING):
	{
		            counterSW4Presstimer = SW4timer;
		            SW4timer = 0;
					ValidCarCommand=true;
					next_Car_command=STATE_RELEASE;
				//	printf("STATE_RELEASE\n");

		break;
	}

	}
}
//Function for Store CarCommand
//Wehn SW4 was pressed read command if valid command store in the carcommand[100] array
//If SW4 plus without any command 3 times jump from loop1 to loop2
void StoreCarCommand_SM(void)
{
	extern volatile bool Firstloop;
	extern volatile bool Secondloop;
	unsigned short int allGPIOBits =  ASM_Read_Switches_GPIO( );
	unsigned short int switchBits =  allGPIOBits & SWITCHBITS_MASK;
	unsigned short int SW_1_3MASK = 0x0700;
	unsigned short int read_1_3_value = switchBits & SW_1_3MASK;
	unsigned char commandvalue = read_1_3_value>>8;
	if(ValidCarCommand==true)
	{
		//if 1 second delete previous command
		if (counterSW4Presstimer  > 150 && counterSW4Presstimer < 350 )
		{
			if(CarcommandNum != 0)
			{
			CarcommandNum--;
			}
		}
		//if press 2 second store car command
		else if (counterSW4Presstimer  > 400 && counterSW4Presstimer < 600)//reset Valid car command to false
		{
			CarCommand[CarcommandNum] = commandvalue;
			CarcommandNum++;
		}
		else if(counterSW4Presstimer  > 650 && counterSW4Presstimer < 850)
		{
			CarCommand[CarcommandNum] = 0x00;
			CarcommandNum++;
			Firstloop=false;
			Secondloop=true;// control jump out the firstloop
		}
		//if the Carcommand number is 10 jump to drive_car_SM
		if(CarcommandNum==10)
		{
			CarCommand[CarcommandNum] = 0x00;
			CarcommandNum++;
			Firstloop=false;
			Secondloop=true;
		}
		counterSW4Presstimer=0;
		ValidCarCommand = false;
		//if counter ==3 put stop command. and
		 //reset the counter
		// drive car (output the inputs)
	}
}



