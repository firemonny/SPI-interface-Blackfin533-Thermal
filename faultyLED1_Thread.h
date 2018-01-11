/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: nschou 
* Date: Tue 2017/10/17 at 03:53:30 PM 
* File Type: TTCOS Main Header File
*************************************************************************************/

#ifndef FAULTYLEDTHREAD_H
#define FAULTYLEDTHREAD_H

#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>

#include "faultyLED1_Thread.h"

// Prototypes for Faulty Flash code
// *** Fix the code and change the names ***

#define INCORRECT_LED1_CODE true
#define INCORRECT_LED3_CODE true
#define INCORRECT_LED5_CODE true
void Faulty_Flash_LED1_If_Then_Else(void);
void Faulty_Flash_LED3_StateMachinePoorExample(void);
void Faulty_Flash_LED5_StateMachineClearExample(void);

void Reset_Faulty_Flash_LED_StateMachines(void);

void Bitwise_Flash_LED1_If_Then_Else(void);
void Bitwise_Flash_LED3_StateMachinePoorExample(void);
void Bitwise_Flash_LED5_StateMachineClearExample(void);

void Reset_Bitwise_Flash_LED_StateMachines(void);

#endif
