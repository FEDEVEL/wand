/**
  PWM4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm4.c

  @Summary
    This is the generated driver implementation file for the PWM4 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for PWM4.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16LF1829
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
         MPLAB 	          :  MPLAB X 6.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "pwm4.h"

/**
  Section: Macro Declarations
*/

#define PWM4_INITIALIZE_DUTY_VALUE    79

/**
  Section: PWM Module APIs
*/

void PWM4_Initialize(void)
{
    // Set the PWM4 to the options selected in the User Interface
	
	// CCP4M PWM; DC4B 3; 
	CCP4CON = 0x3C;    
	
	// CCPR4L 19; 
	CCPR4L = 0x13;    
	
	// CCPR4H 0; 
	CCPR4H = 0x00;    

	// Selecting Timer 2
	CCPTMRSbits.C4TSEL = 0x0;
    
}

void PWM4_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR4L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP4CON = ((uint8_t)(CCP4CON & 0xCF) | ((dutyValue & 0x0003)<<4));
}

/**
 End of File
*/

