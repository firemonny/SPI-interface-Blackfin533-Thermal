/*
 * SPI_Control.h
 *
 *  Created on: Dec 1, 2017
 *      Author: nschou
 */

#ifndef SPI_CONTROL_H_
#define SPI_CONTROL_H_

#include "blackfin.h"


#define SPI_INTERFACE__MASK 0x0020

void Enable_SPI_GPIO(void);
void Set_Up_SPI_Control_Register();
void Init_SPI(void);

#endif /* SPI_CONTROL_H_ */
