/*
 * CalculateTemp_SM.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: nschou
 */
#include "CalculateTemp_SM.h"
enum calculate_temp_SM {FirstBuffer, SecondBuffer};
extern unsigned long int FirstBufferT1[10];
extern unsigned long int SecondBufferT1[10];
extern unsigned long int FirstBufferT2[10];
extern unsigned long int SecondBufferT2[10];
extern float FirstBufferTemperture[10];
extern float SecondBufferTemperture[10];
extern float current_Temperture;
extern float past_Temperature;


void CalculateTemp_SM()
	{
	static calculate_temp_SM current_calculate_temp_state = FirstBuffer;
	switch(current_calculate_temp_state)
	{
	case(FirstBuffer):

		CalculatetempArray(FirstBufferT1,FirstBufferT2,FirstBufferTemperture);
		Bubblesort(FirstBufferTemperture, 10);
		past_Temperature = current_Temperture;
		current_Temperture = calculatecurrenttemp(FirstBufferTemperture);
		current_calculate_temp_state = SecondBuffer;

		break;
	case(SecondBuffer):
		CalculatetempArray(SecondBufferT1,SecondBufferT2,SecondBufferTemperture);
		Bubblesort(SecondBufferTemperture, 10);
		past_Temperature = current_Temperture;
		current_Temperture = calculatecurrenttemp(SecondBufferTemperture);
		current_calculate_temp_state = FirstBuffer;
		break;
	}
	}

void Bubblesort(float* pTarget, int Arraysize)
{

	for(int i=0;i<Arraysize;i++)
	{
		float current = pTarget[i];
		for(int j = i +1; j<Arraysize;j++)
		{
			unsigned long int compare =pTarget[j];
			if(current> compare)
				{
				float temp = current;
					pTarget[i] = pTarget[j];
					pTarget[j] = temp;
				}
		}
	}
}
void CalculatetempArray(unsigned long int *pT1Array,unsigned long int *pT2Array,float *temparray)
{
	//discard the first and end value
	for (int i= 0; i < 10 ;i++)
{
		temparray[i]= 235-((400.0 * (pT1Array[i]))/pT2Array[i]);
}
}

float calculatecurrenttemp(float* pTarget)
{
	float sum =0;
	for (int i =1 ; i <9;i++)
	{
		sum += pTarget[i];
	}
	float return_temp = sum/8.0;
	return return_temp;
}
