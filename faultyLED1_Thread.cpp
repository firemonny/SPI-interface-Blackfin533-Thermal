/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: nschou 
* Date: Tue 2017/10/17 at 03:53:30 PM 
* File Type: TTCOS Faulty Flash code File
*************************************************************************************/

// This is an example of uTTCOS threads.



#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>

#include "faultyLED1_Thread.h"   // Should include links to other project header files

//#warning "Each of these routines work -- on their own but not together -- fix to work correctly"
// Flash LED1
#if INCORRECT_LED1_CODE
	static bool LED1_is_on = false;
void Faulty_Flash_LED1_If_Then_Else(void) {
	if (!LED1_is_on) {
		Write_LED_GPIOInterface(0x1 << (1 - 1));  // Turn on LED 1
		LED1_is_on = true;
	}
	else {
		Write_LED_GPIOInterface(0);  // Turn off LED 1
		LED1_is_on = false;
	}
}
#else
	static bool LED1_is_on = false;
void Bitwise_Flash_LED1_If_Then_Else(void) {

	if (!LED1_is_on) {
		Write_LED_GPIOInterface(0x1 << (1 - 1));  // Turn on LED 1
		LED1_is_on = true;
	}
	else {
		Write_LED_GPIOInterface(0);  // Turn off LED 1
		LED1_is_on = false;
	}
}
#endif

#define TO_UNDERSTAND TODO
//#error -- This is a deliberate fault to get you to read the following code
// void Reset_Faulty_Flash_LED_StateMachines(void) {
// TO_UNDERSTAND 1) 
//       This function will play a key role in making Lab 0 / Assignment 1 test code to work
// }

//  TO_UNDERSTAND 2) 
//      Doing a redefine or understanding the way that Read_LED_GPIOInterface( ) and Write_LED_GPIOInterface( )
//      really operate will play a key role in making Lab 0 / Assignment 1 test code work
//               and in getting Lab 0 / Assignment 1 uTTCOS system to flash LEDs correctly

//  TO_UNDERSTAND 3)
//  currently we have
//  unsigned char Read_LED_GPIOInterface(void)    and void Write_LED_GPIOInterface(unsigned char value);
//      unsigned char LEDresult = Read_LED_GPIOInterface();
//      and then do  CHECK_EQUAL(6, LEDresult);  to compare values

//  Why to do the CHECK_EQUAL macros give MORE understandable results if we used these functions
//        unsigned int myReadLED(void) {  (unsigned int) uTTCOS_ReadLED(); } 
//        void myWriteLED(unsigned int value) { Write_LED_GPIOInterface( (unsigned char) (value & 0x3F)); }
//			unsigned int LEDresult = myReadLED( );
//			and do CHECK_EQUAL(6, LEDresult);    to compare values 

//  TO_UNDERSTAND 4
//  What does this approach to programming the LEDs make their operation more understandable?
//
//  #define BIT_PATTERN  unsigned int
//        BIT_PATTERN myReadLEDBitPattern(void) {  (BIT_PATTERN) uTTCOS_ReadLED(); } 
//        void myWriteLEDBitPattern(BIT_PATTERN value) { Write_LED_GPIOInterface( (unsigned char) (value & 0x3F)); }
//		  BIT_PATTERN LEDresult = myReadLEDBitPattern( );
//		  CHECK_EQUAL(6, LEDresult);

//  TO_UNDERSTAND 5  -- A new test macro example  
//  #define CHECK_HEX_EQUAL(A_hexValue,B_hexValue) \
//  		if (A_hexValue != B_hexValue) \
//  			fprintf(stderr, "Today %s you made  0x%X != 0x%X at line 0x%X\n", \
//           		__DATE__, A_hexValue, B_hexValue, __LINE__)
 
 
