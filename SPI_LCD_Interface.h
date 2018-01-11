/*
 * SPI_LCD_Interface.h
 *
 *  Created on: Dec 1, 2017
 *      Author: nschou
 */

#ifndef SPI_LCD_INTERFACE_H_
#define SPI_LCD_INTERFACE_H_

#include "stdio.h"
#include "string.h"
#include "blackfin.h"
#include "SPI_Control.h"
#include <uTTCOSg2017/uTTCOSg.h>

#define EOS 0x00
#define SW8_High 0x0100
#define SW8_Low 0xfeff
#define SW10_High 0x0400
#define SW10_Low 0xfbff


void SPI_MessageHandler();
void SendMessageSPI_LCD();
bool SPIReady();
void WriteSPI(unsigned short int SPIvalue);
void onetimedeletethread();

// New idea Lab4
void SPI_Message_OS_Thread();
void ChangeToSPIMessageFormat(char* stringarray,  unsigned short int* APIstringarray);
void SPI_SendOneSPIFormat(unsigned short int value);
//LCD Instruction
void Init_LCDScreen();  //send init data to LCD by SPI
//LCD Data
void MSG511rules();
void ClearScreen();
void MSGMerryChrtimas();
void MSGTemperature();
//void MSG2(void);
#endif /* SPI_LCD_INTERFACE_H_ */
