/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: nschou 
* Date: Fri 2017/12/01 at 03:04:00 PM 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include "uTTCOSg_Lab4_uTTCOSg2017_main.h"



// #warning  "This timing MACRO may need adjusting	to get one second flashes on your board"
#undef  EXECUTE_EVERY_SECOND
#define EXECUTE_EVERY_SECOND 		(5 * uTTCOSg_GetTickFrequency( )) // ADJUST ME


#include <stdio.h>

enum {USE_TIMER_OS = 1, USE_AUDIO_OS = 2, DEFAULT_OS = 2, INIT_BOTH_OS_USE_AUDIO_OS = 3};
extern int whichOS;


// TODO "Add C++ prototypes for each new thread you add to the system"
#if defined(__ADSPBF533__)
// #warning  "Read class notes on why this prototype does not have the correct format"
void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 

#elif defined(__ADSP21469__)
extern "C" void SHARC21469_uTTCOSg_Audio_Rx_Tx_Task(void);
#else
	#error "Unknown processor in Audio thread"
#endif	

// #warning "Fix these TODO's, then delete warning and TODO lines
	// TODO  The call to uTTCOSg_AudioTalkThrough will cause a link error because of a missing file
	// TODO  You will need to add the file "BlackfinBF533_uTTCOSg_AudioPremptive_Task.cpp" 
	// TODO      to the project src directory. This file can be found in 
	// TODO            "C:\__CCES\AudioCapture_Files\"
	
	// TODO  The calls to uTTCOSg and GPIO functions will cause link errors until you add their libraries into the project
	// TODO       To add these libraries -- Right click on project name, select Properties, Setting, Library
	// TODO           Select "Add Library" then "Workspace"
	// TODO           "File libraries can be found at "C:\__CCES\Libraries\"
volatile char SPI_MessageToSend[200];
volatile unsigned short int SPIMeassageFormat[600];
void main(void) {
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 12;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

#if defined(__ADSPBF533__)
#if 1
	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);
//	uTTCOSg_AddPreEmptiveThread(BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task, NO_DELAY, EVERY_TICK);
#else
	uTTCOSg_OS_Init(USE_TIMER_INTERRUPT, 1000, 0);
#endif
#elif defined(__ADSP21469__)
	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);	// This changes LED pattern to 0xF8 for some reason
//	uTTCOSg_AddPreEmptiveThread(SHARC21469_uTTCOSg_Audio_Rx_Tx_Task, NO_DELAY, EVERY_TICK);
#else
	#error "Unknown processor in OS_Init"
#endif	

// #warning "You will need to activate the next linme to get the LED interface to workr//  Init_LED_GPIOInterface();

//  TODO Add calls to activate I/O Threads to flash LEDs.  
//  TODO Test the calls one at a time to check they work indiviudually -- then run all together to do an acceptance test
//	uTTCOSg_AddThread(Faulty_Flash_LED1_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOSg_AddThread(Faulty_Flash_LED3_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOSg_AddThread(Faulty_Flash_LED5_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);

//  TODO When Flash1, 3 and 5 work -- refactor the code to have STATE machine format
//	uTTCOSg_AddThread(Flash_LED1_StateMachine, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOSg_AddThread(Flash_LED3_StateMachine, NO_DELAY, EXECUTE_EVERY_SECOND / 4);
//	uTTCOSg_AddThread(Flash_LED5_StateMachine, NO_DELAY, EXECUTE_EVERY_SECOND);
	extern unsigned char sendMessageTaskNumber;

	ASM_Initialize_Switch_GPIO();
	Init_LED_GPIOInterface();
	Write_LED_GPIOInterface(0);

	uTTCOSg_Start_Scheduler(maxNumberThreads);   //  Start the scheduler timer
				// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks

	uTTCOSg_AddThread(Enable_SPI_GPIO, NO_DELAY, RUN_ONCE);

	uTTCOSg_AddThread(SPI_Message_OS_Thread, EXECUTE_EVERY_SECOND * 2.0, EXECUTE_EVERY_SECOND/20.0);
	uTTCOSg_AddThread(Init_LCDScreen,EXECUTE_EVERY_SECOND*3.0,RUN_ONCE);
	uTTCOSg_AddThread(MSG511rules,EXECUTE_EVERY_SECOND*5.0,EXECUTE_EVERY_SECOND*30);
	uTTCOSg_AddThread(MSGMerryChrtimas,EXECUTE_EVERY_SECOND*15.0,EXECUTE_EVERY_SECOND*30);
	uTTCOSg_AddThread(MSGTemperature,EXECUTE_EVERY_SECOND*25.0,EXECUTE_EVERY_SECOND*30);
	uTTCOSg_AddThread(ClearScreen,EXECUTE_EVERY_SECOND*7.0,EXECUTE_EVERY_SECOND*5);
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		uTTCOSg_GoToSleep( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}
}

// #warning "Remember to fix these TODO's, then delete warning and TODO lines
