/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: nschou
* Date: Fri 2017/12/01 at 03:04:00 PM
* File Type: uTTCOS Task Header File
*************************************************************************************/

#ifndef UTTCOSG_LAB4_UTTCOSG2017_H
#define UTTCOSG_LAB4_UTTCOSG2017_H

#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>
#include "Thermo_Timer_SM.h"
#include "DisplayLED_SM.h"
#include "CalculateTemp_SM.h"
#include "Thread_PowerOn_Flash_LED6.h"
#include "SPI_Control.h"
#include "SPI_LCD_Interface.h"
// extern "C" void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 
extern "C" void SHARC21469_uTTCOSg_Audio_Rx_Tx_Task(void);
extern "C" void ADSP_SC589_uTTCOSg_Audio_Rx_Tx_Task(void);
extern "C" unsigned short int ASM_Initialize_Switch_GPIO(void);
extern unsigned char IDNarrator = 0;

#endif
