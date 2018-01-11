/*
 * SPI_LCD_Interface.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: nschou
 */
#include "SPI_LCD_Interface.h"

enum Mymessagetype {SETUP,NOMESSAGE, CAHNGING, INSTRUCTION,COMPLETEING};

//enum LCD_state {STATE1, STATE2, STATE3};

volatile bool SPI_IN_USE = false;
volatile Mymessagetype sendMymessage=SETUP;
const char LCDcommandingString[] = {0x30,0x30,0x3C,0x0F,0x01,EOS};
const char fiveoneoneruleString[] ={0x20,0x20,0x35,0x31,0x31,0x20,0x20,0x52,0x55,0x4C,0x45,0x53,EOS};
const char MerryChrtimasString[] = {'M','E','R','R','Y',' ','C','H','R','T','I','M','A','S','S',' ','\0'};
const char clearscrrenString[] = {0x01,EOS};
volatile unsigned long int numberCharactersToSend;
volatile unsigned char sendMessageTaskNumber;
//volatile LCD_state nextState = STATE1; // Enable strobe control line
volatile int messageElement = 0;
volatile int count = 0;


volatile unsigned int SPI_tokenSent = 0;
extern char SPI_MessageToSend[200];
extern unsigned short int SPIMeassageFormat[600];
volatile int messageRequest = 0;
volatile bool SPI_newMessageRequest = false;
volatile bool SPI_isASCII = false;
volatile unsigned int SPIformateCount;


bool SPIReady()
{
if ((*pSPI_STAT & 0x0001)== 0x0001) return true;
else return false;//check SPI ready of not
}

void WriteSPI(unsigned short int SPIvalue)
{
*pSPI_TDBR = SPIvalue;
}



void SPI_Message_OS_Thread()
{
	switch(sendMymessage)
	{
	case(SETUP):
		Set_Up_SPI_Control_Register();
		Init_SPI();
		sendMymessage = NOMESSAGE;
			//Set the LCD inital
	break;
	case(NOMESSAGE):
			if(SPI_newMessageRequest == true)
			{
				sendMymessage = CAHNGING;
			}
			break;
			// No incoming new signal
			// If we recieve the signal go to Changing
	case(CAHNGING):
			//if(SPI_IN_USE==true) return;
			//SPI_IN_USE = true;  //lock the SPI
		ChangeToSPIMessageFormat(SPI_MessageToSend,SPIMeassageFormat);
		sendMymessage = INSTRUCTION;
			break;//Convert the information to SPI format
	case(INSTRUCTION):
			if(SPI_tokenSent == SPIformateCount)
			{
				sendMymessage = COMPLETEING;
			}
			else
			{
				if(!SPIReady()) return;
				WriteSPI(SPIMeassageFormat[SPI_tokenSent]);
				SPI_tokenSent++;
			}
			break;//send out the information to the LCD
	case(COMPLETEING):
			//finish the instruction
		SPI_tokenSent =0;
		SPI_IN_USE = false;
		SPI_newMessageRequest = false;
		sendMymessage = NOMESSAGE;
		break;
	}


}
void ChangeToSPIMessageFormat(char* stringarray,  unsigned short int* SPIstringarray)
{
	unsigned int numChars = strlen(stringarray);
	SPIformateCount=0;
	unsigned short int asciiControlBit;
	unsigned short int controlLine;
	if(SPI_isASCII) asciiControlBit = SW10_High;
	else asciiControlBit = SW10_Low;
	for (int i=0 ;i<numChars;i++)
	{
		controlLine = SW8_Low;
		if(SPI_isASCII)	SPIstringarray[SPIformateCount] = (stringarray[i] | asciiControlBit) & controlLine;
		else SPIstringarray[SPIformateCount] = (stringarray[i] & asciiControlBit) & controlLine;
		SPIformateCount++;
		controlLine = SW8_High;
		if(SPI_isASCII) SPIstringarray[SPIformateCount] = (stringarray[i] | asciiControlBit) | controlLine;
		else SPIstringarray[SPIformateCount] = (stringarray[i] & asciiControlBit) | controlLine;
		SPIformateCount++;
		controlLine = SW8_Low;
		if(SPI_isASCII) SPIstringarray[SPIformateCount] = (stringarray[i] | asciiControlBit) & controlLine;
		else SPIstringarray[SPIformateCount] = (stringarray[i] & asciiControlBit) & controlLine;
		SPIformateCount++;
	}
}
void Init_LCDScreen()
{
	if(SPI_IN_USE==true) return;

	SPI_IN_USE=true;
	SPI_newMessageRequest =true;
	SPI_isASCII = false;
	strcpy(SPI_MessageToSend,LCDcommandingString);
}
void MSG511rules()
{
	if(SPI_IN_USE==true) return;
	SPI_IN_USE=true;
	SPI_newMessageRequest =true;
	SPI_isASCII = true;
	sprintf(SPI_MessageToSend,fiveoneoneruleString);
}
void ClearScreen()
{
	if(SPI_IN_USE==true) return;
		SPI_IN_USE=true;
		SPI_newMessageRequest =true;
		SPI_isASCII = false;
		sprintf(SPI_MessageToSend,clearscrrenString);

}
void MSGMerryChrtimas()
{

	if(SPI_IN_USE==true) return;
		SPI_IN_USE=true;
		SPI_newMessageRequest =true;
		SPI_isASCII = true;
		sprintf(SPI_MessageToSend,MerryChrtimasString);
}
void MSGTemperature(){
	if(SPI_IN_USE==true) return;
			SPI_IN_USE=true;
			SPI_newMessageRequest =true;
			SPI_isASCII = true;
			sprintf(SPI_MessageToSend,"Temperture is 25 C");
}
/*
void Init_LCDScreen()
{
	if(SPI_IN_USE==true) return;

	SPI_IN_USE=true;
	strcpy(SPImessage,LCDcommandingString);
	sendMymessage = INSTRUCTION;
}


void SPI_MessageHandler()
{
	switch (sendMymessage)
		{
		case(NOMESSAGE):
						break;
		case(DATA):
		numberCharactersToSend = strlen(SPImessage);
		SendMessageSPI_LCD();
		// sendMessageTaskNumber = uTTCOSg_AddThread(SendMessageSPI_LCD, NO_DELAY, EXECUTE_EVERY_SECOND / 20);
		// SendMessageSPI_LCD();
			break;
		case(INSTRUCTION):
		numberCharactersToSend = strlen(SPImessage);
		SendMessageSPI_LCD();

		// sendMessageTaskNumber = uTTCOSg_AddThread(SendMessageSPI_LCD, NO_DELAY, EXECUTE_EVERY_SECOND / 20);
		// SendMessageSPI_LCD();
		// change to NOMESSAGE state This state is send the control LCD signal
					break;
		}
}
void SendMessageSPI_LCD()
{

	if (messageElement == (numberCharactersToSend))
	{
	//when the instruction end need to delete the thread
	messageElement = 0;
	sendMymessage = NOMESSAGE;
	SPI_IN_USE = false;
	return;
	}
	switch(nextState)
	{
	case(STATE1):
		unsigned short int SPIvalue = SPImessage[messageElement];
		SPIvalue = SPIvalue & SW8_Low;
		if (sendMymessage == INSTRUCTION)
		{
			SPIvalue = SPIvalue & SW10_Low;
		}
		else if(sendMymessage == DATA)
		{
			SPIvalue = SPIvalue | SW10_High;
		}
		if (!SPIReady( )) return;

		WriteSPI(SPIvalue);
		nextState = STATE2;

		break;
	case(STATE2):
		SPIvalue = SPImessage[messageElement];
		SPIvalue = SPIvalue | SW8_High;
		if (sendMymessage == INSTRUCTION)
				{
					SPIvalue = SPIvalue & SW10_Low;
				}
		else if(sendMymessage == DATA)
				{
					SPIvalue = SPIvalue | SW10_High;
				}
		if (!SPIReady( )) return;
		WriteSPI(SPIvalue);
		nextState = STATE3;

		break;
	case(STATE3):
		SPIvalue = SPImessage[messageElement];
		SPIvalue = SPIvalue & SW8_Low;
		if (sendMymessage == INSTRUCTION)
			{
				SPIvalue = SPIvalue & SW10_Low;
			}
		else if(sendMymessage == DATA)
				{
					SPIvalue = SPIvalue | SW10_High;
				}
		if (!SPIReady( )) return;

		WriteSPI(SPIvalue);
		messageElement++;		// finish the instruction
		nextState = STATE1;

		break;

	}

}*/
