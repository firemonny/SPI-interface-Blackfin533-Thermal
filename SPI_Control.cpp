/*
 * SPI_Control.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: nschou
 */
#include "SPI_Control.h"

void Enable_SPI_GPIO(void)
{
	*pFIO_DIR |= SPI_INTERFACE__MASK;					//make PF5 to be output signal
	*pFIO_POLAR |= SPI_INTERFACE__MASK; 				//selct polarity to PF5
	*pFIO_INEN |= SPI_INTERFACE__MASK;
	*pFIO_MASKA_D &= (~SPI_INTERFACE__MASK);
	*pFIO_MASKB_D &= (~SPI_INTERFACE__MASK);

}
void Set_Up_SPI_Control_Register()
{
	*pSPI_BAUD = 0x8000;    //Set Baud rate to 0x8000;
	*pSPI_STAT = 0x0056;    //Clear out the register
	*pSPI_CTL  = 0x1101;
	*pSPI_FLG = 0xFF20;
}
void Init_SPI(void)
{
	*pSPI_CTL |= 0x4000;//Don't forget the put | 0x4000
	*pSPI_TDBR =0x0000;
}
