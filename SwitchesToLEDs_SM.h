/*
 * SwitchesToLEDs_SM.h
 *
 *  Created on: Oct 7, 2017
 *      Author: nschou
 */

#ifndef SWITCHESTOLEDS_SM_H_
#define SWITCHESTOLEDS_SM_H_



#define SWITCHBITS_MASK 0x0F00			// Use only PF8 to 11
#define SW4_MASK 0x0800						// Mask to check  switch 4 is being pressed


void SwitchesToLEDs_SM(void);
void DriveCar_StateMachine1(void);
void GetCarCommand_SM(void);
void StoreCarCommand_SM(void);
#endif /* SWITCHESTOLEDS_SM_H_ */
