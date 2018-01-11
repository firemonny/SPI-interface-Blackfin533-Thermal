/*
 * DoPrint_C.c
 *
 *  Created on: Oct 10, 2017
 *      Author: nschou
 */
#include "blackfin.h"
#include "stdio.h"
void CPrintCalledFromASM(void) {
     static unsigned int timesUsed = 0;
     timesUsed++;
     printf("C function called from ASM %d\n", timesUsed);
}

void CSetMaskB(void) {
unsigned short int MaskB = 0xf0ff;
unsigned short int temp = *pFIO_MASKB_D;
temp = temp & MaskB;
*pFIO_MASKB_D = temp;
ssync();
}

void CSETLevel(void){
unsigned short int LevelMask = 0xf0ff;
unsigned short int temp = *pFIO_EDGE;
temp = temp & LevelMask;
*pFIO_EDGE = temp;
}

void C_EnableInput(void){
unsigned short int MaskEnable = 0x0f00;
*pFIO_INEN = *pFIO_INEN | MaskEnable;
}
