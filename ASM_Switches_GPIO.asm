#include <blackfin.h>                       // This header file know about Blackfin register names


#define byte4 var
	.section L1_Data;
	
_DUMMYStaticVariable:  .byte4 = 1;

     .section program;
 // extern "C" unsigned  int ASM_Read_Switches_GPIO(void);
// Promise -- this will return the values of PF8 to PF11 in a C++ compatible way in R0
     .global _ASM_Read_Switches_GPIO;
_ASM_Read_Switches_GPIO:
	LINK 16;								// Save a copy of RETS and other magic
	
	                                          // Make a mask to only see PF8 to PF11 bits of the register
#define SW4mask_R1 R1
		SW4mask_R1 = 0x0F00;				//0x0F000  There is extra 0

#define returnValue_R0 R0
		returnValue_R0 = 0;					// unsigned int returnValue = 0;

										// Find the FIO data register name on reference sheet
                                            // Add a p in front of it, 
                                             // and it becomes an unsigned short int pointer
#define pFIO_FLAG_D_P0 P0
    P0.L = lo(FIO_FLAG_D);	
    P0.H = hi(FIO_FLAG_D);   			// Monny add Load the register Hi. Lo. separtely
                                            // Get the GPIO value into the returnValue
                                            // returnValue = *pFIO_DATA_D
// Two approaches -- I prefer the first as it makes top part of R0 = 0 incase C++ thinks it is a unsigned long int
    returnValue_R0 = W[pFIO_FLAG_D_P0] (Z);
//	    R0.L = W[pFIO_FLAG_D_P0];         //Monny change R0.L --> R0.H
//        R0.H = 0;                                    // Keep only PF8 to PF11
                                            // returnValue = returnValue & SW4mask

 returnValue_R0 = returnValue_R0 & SW4mask_R1;
 	
	// Already in R0						// return returnValue
//  W[pFIO_DATA_REGISTER_P0] = R0; This is wrong because we only read the value not write value

    UNLINK;   								// Get back the copy of RETS and other magic                             
_ASM_Read_Switches_GPIO.END:       
	RTS;

//Function for ASM_Initialize_Switch_GPIO

     .global _ASM_Initialize_Switch_GPIO;
_ASM_Initialize_Switch_GPIO:
	LINK 16;	
								// Save a copy of RETS and other magic
	.extern _CPrintCalledFromASM;
     CALL _CPrintCalledFromASM;    // Do the C print Call

 //   .extern _Init_Input_GPIOInterface;
 //     CALL _Init_Input_GPIOInterface;  // Use library call
	//Safely set bits 8 to 11 in MASK-A register to 0 by calling an ASM function void ASM_SETMaskA(void);
	   .extern _ASM_SETMaskA;
	   CALL _ASM_SETMaskA;
	//Safely set bits 8 to 11 in MASK-B register to 0 by calling an C function void C_SETMaskB(void);
	.extern _CSetMaskB;
	  CALL _CSetMaskB;						
//Key things -- POLAR -- set so that if input is 1 then bit is 1 when you read FIO_DATA_D (ASM)
	  .extern _ASM_SETPolarity;
	  CALL _ASM_SETPolarity;
//Key things -- LEVEL -- set so that if input is 1 then bit is 1 when you read FIO_DATA_D (C) ??Which register
	 .extern _CSETLevel;
	 	CALL _CSETLevel;
//Key things -- DIRECTION -- set so that if input is 1 then bit is 1 when you read FIO_DATA_D (ASM)	
	   .extern _ASM_SETDirection;
	   CALL _ASM_SETDirection;
//Set bits 8 to 11 to the correct value in all other FIO_DATA registers by calling ASM functions except 
//FIO_DATA_D is not a device control register 
//(do something to the device) FIO_DATA_D is a register controlled by the device 
//(the device does something to it)
		.extern _C_EnableInput;
		CALL _C_EnableInput;

     .extern _CPrintCalledFromASM;   // My pattern always has a (cut-and-paste) .extern and CALL pair
     CALL _CPrintCalledFromASM;    // Do the C print Call
     
    UNLINK;   								// Get back the copy of RETS and other magic                             
_ASM_Initialize_Switch_GPIO.END:       
	RTS;

// Function for	void ASM_SETMaskA(void)
	.global _ASM_SETMaskA;
_ASM_SETMaskA:
	LINK 16;
	#define MaskA_R1 R1
	R1.L = lo(0xf0ff);
	R1.H = hi(0xf0ff);
	
	
	#define pFIO_MASKA_D_P0 P0
	P0.L = lo(FIO_MASKA_D);	
    P0.H = hi(FIO_MASKA_D);
#define returnValue_R0 R0
		returnValue_R0 = 0;
		R0 = W[P0] (X);
		R0 = R0 & MaskA_R1;
		W[P0] = R0;
    //need ssync
	UNLINK;
_ASM_SETMaskA.END:
	RTS;

// Function for void
//Set bits 8 to 11 to the correct value in all other FIO_DATA registers by calling ASM functions except 
//FIO_DATA_D is not a device control register 
//(do something to the device) FIO_DATA_D is a register controlled by the device 
//(the device does something to it)



	.global _ASM_SETPolarity;
_ASM_SETPolarity:
	LINK 16;
	
	#define PolarityMask_R1 R1
	R1.L = lo(0xf0ff);
	R1.H = hi(0xf0ff);
	//set P0 to the pointer on FIO_POLAR
	#define pFIO_POLAR P0
	P0.L = lo(FIO_POLAR);
	P0.H = Hi(FIO_POLAR);
    //Read P0 value put into R0 register because use the previous SETMASKA function FIO_MASKA_D
    #define returnValue_R0 R0
    returnValue_R0 = 0; 
    returnValue_R0 = W[P0](X);						// unsigned short int var_R0;
	returnValue_R0 = returnValue_R0 & PolarityMask_R1;  
	//Set P1

	// put the vlaue back into the FIO_POLAR
	W[P0] = returnValue_R0;
	UNLINK;
_ASM_SETPolarity.END:
	RTS;

	.global _ASM_SETDirection;
_ASM_SETDirection:
	LINK 16;
	
	#define DirMask_R1 R1
	R1.L = lo(0xf0ff);
	R1.H = hi(0xf0ff);
	//set P0 to the pointer on FIO_POLAR
    #define pFIO_DIR_P1 P0
	P0.L = lo(FIO_DIR);
	P0.H = hi(FIO_DIR);
    //Read P0 value put into R0 register because use the previous SETMASKA function FIO_MASKA_D
    #define returnValue_R0 R0
    returnValue_R0 = 0;
    R0 = W[P0](X);
    R0 = R0 & DirMask_R1;
	W[P0] = R0;
	UNLINK;
_ASM_SETDirection.END:	
	RTS;
	
	
	