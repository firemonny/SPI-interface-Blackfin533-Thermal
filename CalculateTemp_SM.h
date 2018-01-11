/*
 * CalculateTemp_SM.h
 *
 *  Created on: Nov 28, 2017
 *      Author: nschou
 */

#ifndef CALCULATETEMP_SM_H_
#define CALCULATETEMP_SM_H_

#include "blackfin.h"
#include <GPIO2017/ADSP_GPIO_Interface.h>
#include "stdio.h"

void CalculateTemp_SM();
void Bubblesort(float* pTarget, int Arraysize);
void CalculatetempArray(unsigned long int *pT1Array,unsigned long int *pT2Array,float *temparray);
float calculatecurrenttemp(float* pTarget);
#endif /* CALCULATETEMP_SM_H_ */
