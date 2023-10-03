/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16LF1829
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

#define KXTJ3_I2C_ADDR 0x0E
#define KXTJ3_WHO_AM_I 0x0F

#define X 0
#define Y 1
#define Z 2

char detectMovementDirection(int8_t axis[], int8_t prev_axis[]) {
    //If there is more movement in Y axis (tilt), detect Up or Down tilt
    if ((abs(axis[Y] - prev_axis[Y])) > (abs(axis[X] - prev_axis[X]))) {
        if ((axis[Y] > prev_axis[Y]) && (abs(axis[Y] - prev_axis[Y]) > 10)) {
            return 'U';
        }
        if ((axis[Y] < prev_axis[Y]) && (abs(axis[Y] - prev_axis[Y]) > 10)) {
            return 'D';
        }
    }
    //If there is more movement in X axis (roll), detect Left or Right roll
    else if ((abs(axis[Y] - prev_axis[Y])) < (abs(axis[X] - prev_axis[X]))) {
        if ((axis[X] > prev_axis[X]) && (axis[Z] < prev_axis[Z]) && (abs(axis[X] - prev_axis[X]) > 25)) {
            return 'L';
        }
        if ((axis[X] < prev_axis[X]) && (axis[Z] < prev_axis[Z]) && (abs(axis[X] - prev_axis[X]) > 25)) {
            return 'R';
        }
    }
    //If there is not enough movement, fill sequence with empty "X"
    return 'X';
}

void lumos() {
    printf("\n\r LUMOS \n\r");
    //Turn on yellowish light
    EPWM1_LoadDutyValue(15); //B
    EPWM2_LoadDutyValue(160); //R
    PWM4_LoadDutyValue(160); //G
}

void nox() {
    printf("\n\r NOX \n\r");
    //Turn off lumos light
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
}

void dark_magic_enter() {
    printf("\n\r DARK MAGIC STATE \n\r");
    //Turn on red glow
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(10); //R
    PWM4_LoadDutyValue(0); //G
}

void expecto_patronum() {
    printf("\n\r EXPECTO PATRONUM \n\r");
    DELAY_milliseconds(1000);
    //Turn on blue glow
    EPWM1_LoadDutyValue(20); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(200);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(200);
    EPWM1_LoadDutyValue(80); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(200);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(200);
    EPWM1_LoadDutyValue(160); //B
    EPWM2_LoadDutyValue(10); //R
    PWM4_LoadDutyValue(10); //G
    DELAY_milliseconds(4000);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0); //G
}

void avada_kedavra() {
    printf("\n\r AVADA KEDAVRA \n\r");
    //Turn on green glow
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(20); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(40); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(60); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(80); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(160); //G
    DELAY_milliseconds(2500);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(10); //R
    PWM4_LoadDutyValue(0); //G
}

void crucio() {
    printf("\n\r CRUCIO \n\r");
    //Turn on green glow
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(50); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(100); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(20); //B
    EPWM2_LoadDutyValue(50); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(50); //B
    EPWM2_LoadDutyValue(100); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(300);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(160); //R
    PWM4_LoadDutyValue(0); //G
    DELAY_milliseconds(2500);
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(10); //R
    PWM4_LoadDutyValue(0); //G
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    /* **************** INTERRUPT WORKFLOW **************** */
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    /* **************** INTERRUPT WORKFLOW **************** */

    printf("\n\r Starting ... \n\r"); 
    //RESET LEDS
    EPWM1_LoadDutyValue(0); //BLUE
    EPWM2_LoadDutyValue(0); //RED
    PWM4_LoadDutyValue(0); //GREEN 
    printf("\n\r 1 ... \n\r");
    
    /*EPWM2_LoadDutyValue(100); //RED
    DELAY_milliseconds(1000);            
    EPWM2_LoadDutyValue(0); //RED
    PWM4_LoadDutyValue(100); //GREEN 
    DELAY_milliseconds(1000);            
    PWM4_LoadDutyValue(0); //GREEN     
    EPWM1_LoadDutyValue(100); //BLUE
    DELAY_milliseconds(1000);        
    EPWM1_LoadDutyValue(0); //BLUE */
    
    /*uint8_t initialization_data;
    data = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, KXTJ3_WHO_AM_I);
    
    if(data == 0x35)
        PWM4_LoadDutyValue(160); //green
    else
        EPWM2_LoadDutyValue(160); //red
    DELAY_milliseconds(1000);*/
    
    
    printf("\n\r 2 ... \n\r");
    
    //Initialize accelerometer
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1D, 0b10000000); // reset acceletometer
    DELAY_milliseconds(1000); //wait until the reset sequence is finished
    
    printf("\n\r 3 ... \n\r");
    
    //Set registers for what we need to test
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1E, 0b00101000);
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1F, 0b10111111);    
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b00000000);    
    //I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b00000010);
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b10000010);
    //I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b10000000);
    
    //initialization_data = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x1B); //read this register to clear interrupts
    
    //RESET LEDS
    EPWM1_LoadDutyValue(0); //BLUE
    EPWM2_LoadDutyValue(0); //RED
    PWM4_LoadDutyValue(0); //GREEN
    
    printf("\n\r 4 ... \n\r");
    
    int8_t discrete_counter = 0; //Spell time window counter

    int8_t axis[3];
    int8_t prev_axis[3];
    
    prev_axis[X] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07);
    prev_axis[Y] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
    prev_axis[Z] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x0B);
    
    //Spell movements buffer - 0 index = newest, 3 index = oldest
    char spell_movements[4] = {'N', 'N', 'N', 'N'};
 
    char casting_state; //Current state of state machine
    
    
    if (prev_axis[Z] <= -50) {
        //If the wand is upside down, enter debug mode
        
        casting_state = 'D';
        
        EPWM2_LoadDutyValue(100); //RED ON
        DELAY_milliseconds(1000); //1s
        EPWM2_LoadDutyValue(0); //RED OFF
        PWM4_LoadDutyValue(100); //GREEN ON
        DELAY_milliseconds(1000); //1s
        PWM4_LoadDutyValue(0); //GREEN OFF
        EPWM1_LoadDutyValue(100); //BLUE ON
        DELAY_milliseconds(1000); //1s
        EPWM1_LoadDutyValue(0); //BLUE OFF
    }
    else {
        //If the wand is in normal orientation, enter spell mode
        casting_state = 'S';
    }
        
    
    
    printf("\n\r Running ... \n\r");
    while (1)
    {
        if (discrete_counter == 0) { //If discrete time window is active
            //Get accelerometer axis
            axis[X] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07);
            axis[Y] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
            axis[Z] = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x0B);
        
            //printf("%d %d %d \n\r", axis[X], axis[Y], axis[Z]);

            //Shift spell movements buffer, Add new movement to buffer
            spell_movements[3] = spell_movements[2];
            spell_movements[2] = spell_movements[1];
            spell_movements[1] = spell_movements[0];
            spell_movements[0] = detectMovementDirection(axis, prev_axis);
        }
        
        //Register current axis data as previous data for next step
        prev_axis[X] = axis[X];
        prev_axis[Y] = axis[Y];
        prev_axis[Z] = axis[Z];
        
        //Debug spell movements
        printf("%c %c %c %c \n\r", spell_movements[0], spell_movements[1], spell_movements[2], spell_movements[3]);
        
        //START STATE MACHINE
        if (casting_state == 'D') {
            //DEBUG STATE, NO SUCCESSOR NODES
            
            //Change RGB color based on wand orientation
            if (axis[X] > 0) {
                EPWM1_LoadDutyValue(axis[X]);
            }
            else {
                EPWM1_LoadDutyValue(axis[X] * (-1));
            }

            if (axis[Y] > 0) {
                EPWM2_LoadDutyValue(axis[Y]);
            }
            else {
                EPWM2_LoadDutyValue(axis[Y] * (-1));
            }

            if (axis[Z] > 0) {
                PWM4_LoadDutyValue(axis[Z]);
            }
            else {
                PWM4_LoadDutyValue(axis[Z] * (-1));
            }
            
        }
        if (casting_state == 'S') {
            //STARTING POSITION
            //Detect dark magic state change
            if ((axis[Z] <= -60) && 
               (spell_movements[0] == 'X') && (spell_movements[1] == 'X') && (spell_movements[2] == 'X') && (spell_movements[3] == 'X')) {
                //Change state to dark magic starting state
                dark_magic_enter();
                casting_state = 'M';
                
                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }

            //Detect lumos casting
            else if ((((spell_movements[0] == 'U') || (spell_movements[1] == 'U')) && ((spell_movements[2] == 'D') || (spell_movements[3] == 'D')))
               && (axis[Y] <= 35)) {
                //Cast lumos and enter lumos state
                lumos();
                casting_state = 'L';

                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
            
            //Detect expecto patronum casting
            else if ((((spell_movements[0] == 'X') && (spell_movements[1] == 'X')) && ((spell_movements[2] == 'X') && (spell_movements[3] == 'X')))
               && (axis[Y] >= 62)) {
                //Cast expecto_patronum, stay in white magic state
                expecto_patronum();
                casting_state = 'S';

                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
            
            
        }
        else if (casting_state == 'L') {
            //Wait for nox condition inside lumos state
            
            if ((((spell_movements[0] == 'L') || (spell_movements[1] == 'L')) && 
               ((spell_movements[2] == 'R') || (spell_movements[3] == 'R'))) && 
               (abs(axis[X]) >= 40)) {

                nox();
                casting_state = 'S';
                
                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
        }
        else if (casting_state == 'M') {
            //Wait for dark spell or white magic condition
            
             //Detect white magic state change
            if ((axis[Z] >= 60) && 
               (spell_movements[0] == 'X') && (spell_movements[1] == 'X') && (spell_movements[2] == 'X') && (spell_movements[3] == 'X')) {
                //Change state to white magic starting state, use nox to reset LED
                nox();
                casting_state = 'S';
                
                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
            
            //Detect avada kedavra
            else if ((((spell_movements[0] == 'L') || (spell_movements[1] == 'L')) && ((spell_movements[2] == 'D') || (spell_movements[3] == 'D')))
               && (axis[Y] <= 35)) {
                //Cast avada kedavra
                avada_kedavra();
                casting_state = 'M';

                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
            
            //Detect dark magic transition state
            else if ((((spell_movements[0] == 'X') && (spell_movements[1] == 'X')) && ((spell_movements[2] == 'X') && (spell_movements[3] == 'X')))
               && (axis[Y] <= -60)) {
                casting_state = 'T';

                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }

        }
        else if (casting_state == 'T') {
            //Wait for dark spell
            
             //Detect crucio
            if ((axis[Y] >= -5) && 
               (spell_movements[0] == 'X') && (spell_movements[1] == 'X') && (spell_movements[2] == 'X') && (spell_movements[3] == 'X')) {
                //Change state to white magic starting state, use nox to reset LED
                crucio();
                casting_state = 'M';
                
                //Reset current spell movements buffer
                spell_movements[0] = 'N';
                spell_movements[1] = 'N';
                spell_movements[2] = 'N';
                spell_movements[3] = 'N';
            }
        }
        
        discrete_counter++;
        //printf("%d \n\r n\nr", discrete_counter);
        if (discrete_counter >= 8) {
            //printf("%d \n\r n\nr", i);
            
            /*spell_movements[0] = 'X';
            spell_movements[1] = 'X';
            spell_movements[2] = 'X';
            spell_movements[3] = 'X';*/
            
            discrete_counter = 0;
        }
        
    }
}
/**
 End of File
*/