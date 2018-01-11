
#include "Thread_PowerOn_Flash_LED6.h"
#include "stdio.h"

#define LEDBITS unsigned char
#define LED6 0x20
enum LED6_STATE {LED6_SUPPOSED_TO_BE_OFF, LED6_SUPPOSED_TO_BE_ON};


void PowerOn_Flash_LED6(void){
	static LED6_STATE nextTime = LED6_SUPPOSED_TO_BE_ON;
	LEDBITS currentLEDvalue = Read_LED_GPIOInterface();
	LEDBITS newLEDvalue = currentLEDvalue;
	switch (nextTime) {
	case LED6_SUPPOSED_TO_BE_OFF:
	  newLEDvalue = newLEDvalue & ~LED6;
	  nextTime = LED6_SUPPOSED_TO_BE_ON;
	  break;
	case LED6_SUPPOSED_TO_BE_ON:
	  newLEDvalue = newLEDvalue | LED6;
	  nextTime = LED6_SUPPOSED_TO_BE_OFF;
	  break;
	default:
	  printf("Should never get here in FlashLED6\n");
	}
	Write_LED_GPIOInterface(newLEDvalue);
}

static volatile unsigned long int LED6_threadCounter = 0;
static volatile unsigned long int LED6_threadPeriod = 0;

void Initialize_Thread_PowerOn_Flash_LED6(unsigned long int delay, unsigned long int period) {
   LED6_threadCounter = delay;
   LED6_threadPeriod = period;
}

// void PowerOn_Flash_LED6(void);  -> Dr. Smith's code
void Thread_PowerOn_Flash_LED6(void) {
// If I make a "one-out" logical error -- this code will fail
//   meaning LED 6 will tick (just a little) too slowly or too fast
//   -- so check the logic carefully
   if (LED6_threadCounter == 0) {
      PowerOn_Flash_LED6();
      LED6_threadCounter = LED6_threadPeriod;
   }

   LED6_threadCounter--;
}
