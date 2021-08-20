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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
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

void WakeUpInterrupt(void);
void ButtonInterrupt(void);
void TimerInterrupt(void);

int8_t moves[4];
int8_t part = 1;

//extern uint8_t intensity_red = 0;
//extern uint8_t intensity_green = 0;
//extern uint8_t intensity_blue = 0;

//Absolute Value function
int8_t mathAbs(int8_t num){
    if(num > 0)
        return num;
    else if(num < 0)
        return -num;
    else
        return 0;
}

int8_t mathSign(int8_t num){
    if(num > 0)
        return 1;
    else if(num < 0)
        return -1;
    else
        return 0;
}

int8_t mathMin(int8_t n, int8_t m){
    if(n > m){
        return m;
    }else{
        return n;
    }
}

//Simple LED effect
void patronus(void)
{
    EPWM1_LoadDutyValue(0); //BLUE
    EPWM2_LoadDutyValue(0); //RED
    PWM4_LoadDutyValue(0); //GREEN
    
    uint8_t i;
    
    //start with blue
    for (i=0;i<20;i++)
    {
        EPWM1_LoadDutyValue(i);
        DELAY_milliseconds(100);
    }
    
    //change to white
    for (i=0;i<20;i++)
    {
        EPWM2_LoadDutyValue(i);
        PWM4_LoadDutyValue(i);
        DELAY_milliseconds(100);
    }      
    
    //go to the full white intensity
    for (i=20;i<100;i++)
    {
        EPWM1_LoadDutyValue(i); //BLUE
        EPWM2_LoadDutyValue(i); //RED
        PWM4_LoadDutyValue(i); //GREEN 
        DELAY_milliseconds(10);
    }    
    
    DELAY_milliseconds(3000); //full brightness for 3s
    
    //slowly turn off the LEDs
    for (i=100;i>1;i--)
    {
        EPWM1_LoadDutyValue(i); //BLUE
        EPWM2_LoadDutyValue(i); //RED
        PWM4_LoadDutyValue(i); //GREEN 
        DELAY_milliseconds(10);
    }        
    EPWM1_LoadDutyValue(0); //BLUE
    EPWM2_LoadDutyValue(0); //RED
    PWM4_LoadDutyValue(0); //GREEN    
}

void lumos(){
    int8_t on = 1;
    EPWM1_LoadDutyValue(10); //B
    EPWM2_LoadDutyValue(100); //R
    PWM4_LoadDutyValue(85);
    DELAY_milliseconds(100);
    int8_t previous = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
    while(on){
        
        
        if(mathAbs(I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09)-previous) > 20){
            on = 0;
        }
        /*
        previous = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
        
        //printf("Hi");
        int8_t tmp = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07);
        //printf("%04d \n\r", tmp);
        //printf("%04d \n\r", tmp/2);
        //tmp = tmp+1;
        //printf(tmp);
        //printf(tmp+1);
        //printf("%04d %04d %04d \n\r", 10 + tmp*0.1, 80 + tmp, 65 + tmp*0.8);
        
        EPWM1_LoadDutyValue(10 + (I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07))*0.1); //B
        EPWM2_LoadDutyValue(80 + (I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07))); //R
        PWM4_LoadDutyValue(65 + (I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07))*0.8);
        */
        
        //Full light, yellowish
        EPWM1_LoadDutyValue(11); //B
        EPWM2_LoadDutyValue(160); //R
        PWM4_LoadDutyValue(160);
    }
    
}

void lightsOff(){
    EPWM1_LoadDutyValue(0); //B
    EPWM2_LoadDutyValue(0); //R
    PWM4_LoadDutyValue(0);
}

void flashRED()
{
    uint8_t i; 
    EPWM2_LoadDutyValue(160); //RED
    DELAY_milliseconds(100);
    for (i=20;i>0;i--)
    {
        EPWM2_LoadDutyValue(i); //RED
        DELAY_milliseconds(1);
    }    
    lightsOff(); 
}

void flashWhite()
{
    uint8_t i; 
    EPWM1_LoadDutyValue(160); //B
    EPWM2_LoadDutyValue(160); //R
    PWM4_LoadDutyValue(160);
    DELAY_milliseconds(100);
    for (i=20;i>0;i--)
    {
        EPWM1_LoadDutyValue(i); //B
        EPWM2_LoadDutyValue(i); //R
        PWM4_LoadDutyValue(i);
        DELAY_milliseconds(1);
    }    
    lightsOff(); 
}

void sparks(){
    
    uint8_t i;    
    
    //go to the full white intensity
    /*for (i=0;i<50;i++)
    {
        EPWM1_LoadDutyValue(i); //BLUE
        EPWM2_LoadDutyValue(i+10); //RED
        PWM4_LoadDutyValue(i); //GREEN 
        DELAY_milliseconds(30);
    }  */
    
    /*
    for (i=0;i<50;i+=2)
    {
        EPWM1_LoadDutyValue(50-i); //BLUE
        EPWM2_LoadDutyValue(i+60); //RED
        PWM4_LoadDutyValue(50-i); //GREEN 
        DELAY_milliseconds(40);
    }
     */
    
    lightsOff();
    
    for (i=0;i<160;i++)
    {
        EPWM2_LoadDutyValue(i); //RED
        DELAY_milliseconds(10);
    }  
  
    lightsOff();
    DELAY_milliseconds(400);     

    flashRED(); 
    DELAY_milliseconds(400); 
    
    flashRED(); 
    DELAY_milliseconds(50); 
    
    flashRED(); 
    DELAY_milliseconds(50); 
    
    flashRED(); 
    DELAY_milliseconds(300); 
    
    flashRED(); 
    DELAY_milliseconds(20); 
    
    flashRED(); 
    DELAY_milliseconds(20); 
    
    flashRED(); 
    DELAY_milliseconds(20); 
    
    flashRED(); 
    DELAY_milliseconds(100); 
    
    flashRED(); 
    DELAY_milliseconds(20); 
    
    flashRED(); 
    DELAY_milliseconds(20); 
    
    flashRED(); 
    DELAY_milliseconds(20);     

    flashRED();  
    DELAY_milliseconds(20);        
    
    
    //PWM4_LoadDutyValue(160); //GREEN 
    //DELAY_milliseconds(1000);    
    /*
    for(i = 1; i < 12; i++){
        EPWM1_LoadDutyValue(((i*197)%8)*5); //BLUE
        EPWM2_LoadDutyValue(((i*391)%8)*10+80); //RED
        PWM4_LoadDutyValue(((i*357)%3)*10); //GREEN 
        
        DELAY_milliseconds(((i*2975)%57) + 80);
        
        lightsOff();
        
        DELAY_milliseconds(((i*2975)%89) + 120);
    }
     */
    
    lightsOff();
    
    //for (i=10;i>0;i--)
    //{
    //    EPWM2_LoadDutyValue(i); //R  
    //    DELAY_milliseconds(40);
    //}
    //DELAY_milliseconds(200);
    
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    //Handle interrupts
    //INT_SetInterruptHandler(WakeUpInterrupt); //Set Weakup Interrupt from accelerometer handler   
    IOCBF7_SetInterruptHandler(ButtonInterrupt); //Set Button Interrupt handler
    //TMR4_SetInterruptHandler(TimerInterrupt); //Set Timer interrupt handler
    
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

    //Turn OFF all the LEDs
    EPWM1_LoadDutyValue(0);
    EPWM2_LoadDutyValue(0);
    PWM4_LoadDutyValue(0);
    
    uint8_t data;
    data = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x0F);
    
    if(data == 0x35)
        PWM4_LoadDutyValue(160); //green
    else
        EPWM2_LoadDutyValue(160); //red
    //DELAY_milliseconds(500);
    
    //initialize accelerometer
    //this still needs to be adjusted, this code doesnt follow the recommended start up sequence
    // read more here: https://kionixfs.azureedge.net/en/document/TN017-Power-On-Procedure.pdf
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1D, 0b10000000); // reset acceletometer
    DELAY_milliseconds(1000); //wait until the reset sequence is finished
    
    //set registers for what we need to test
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1E, 0b00101000);
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1F, 0b10111111);    
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b00000000);    
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b00000010);
    I2C1_Write1ByteRegister(KXTJ3_I2C_ADDR, 0x1B, 0b10000010); 
    
    data = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x1B); //read this register to clear interrupts
    
    //TMR4_StartTimer(); for future use  
    
    int8_t data_x = 0;
    int8_t data_y = 0;
    int8_t data_z = 0;
    
    int8_t max_data_x = 0;
    int8_t max_data_y = 0;
    int8_t max_data_z = 0;
    
    int8_t max_data_x_dir = 0;
    int8_t max_data_y_dir = 0;
    int8_t max_data_z_dir = 0;
    
    int8_t previous_data_x = 0;
    int8_t previous_data_y = 0;
    int8_t previous_data_z = 0;
    
    int8_t timer = 0;
    
    //EUSART_Write(0x30);
    //printf("\n\r Hello \n\r");
    
    while (1)
    {
        //test code - turns on different LED color when PCB is oriented different ways
       
        
        //EPWM1_LoadDutyValue(0);
        //EPWM2_LoadDutyValue(0);
        //PWM4_LoadDutyValue(0);
        
        max_data_x = 0;
        max_data_y = 0;
        max_data_z = 0;
        max_data_x_dir = 1;
        max_data_y_dir = 1;
        max_data_z_dir = 1;
        
        int8_t i;
        //for (i=0;i<75;i++)
        //{
           
            data_x = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07);
            data_y = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
            data_z = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x0B);
            
            //printf("%04d %04d %04d \n\r", data_x, data_y, data_z);
        /*    if(mathAbs(data_x-previous_data_x) > max_data_x){
                max_data_x = mathAbs(data_x-previous_data_x);
                max_data_x_dir = mathSign(data_x-previous_data_x);
            }
            if(mathAbs(data_y-previous_data_y) > max_data_y){
                max_data_y = mathAbs(data_y-previous_data_y);
                max_data_y_dir = mathSign(data_y-previous_data_y);
            }
            if(mathAbs(data_z-previous_data_z) > max_data_z){
                max_data_z = mathAbs(data_z-previous_data_z);
                max_data_z_dir = mathSign(data_z-previous_data_z);
            }
            DELAY_milliseconds(2);
        }*/
        
        /*if (mathAbs(data_x-previous_data_x) > 5 && mathAbs(data_x-previous_data_x) > mathAbs(data_z-previous_data_z) && mathAbs(data_x-previous_data_x) > mathAbs(data_y-previous_data_y)){
            EPWM1_LoadDutyValue(200);
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(0);
            DELAY_milliseconds(200);
        }else if (mathAbs(data_y-previous_data_y) > 5 && mathAbs(data_y-previous_data_y) > mathAbs(data_x-previous_data_x) && mathAbs(data_y-previous_data_y) > mathAbs(data_z-previous_data_z)){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(200);
            PWM4_LoadDutyValue(0);
            DELAY_milliseconds(200);
        }else if (mathAbs(data_z-previous_data_z) > 5 && mathAbs(data_z-previous_data_z) > mathAbs(data_x-previous_data_x) && mathAbs(data_z-previous_data_z) > mathAbs(data_y-previous_data_y)){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(200);
            DELAY_milliseconds(200);
        }*/
        
        //ORIENTATION CHECK
        if (mathAbs(data_x) > mathAbs(data_y) + mathAbs(data_z)){
            EPWM1_LoadDutyValue(0); //1
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(0);
            DELAY_milliseconds(100);
            if(part < 4 && moves[part-1] != 1){
                moves[part] = 1;
                part++;
            }
        }else if (mathAbs(data_y) > mathAbs(data_x) + mathAbs(data_z)){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(0); //Red, so reset moves
            PWM4_LoadDutyValue(0);
            DELAY_milliseconds(100);
            if(part < 4 && moves[part-1] != 2){
                moves[part] = 2;
                part++;  
                timer = 0;
            }
           
            if(moves[1] == 2 && moves[2] == 1 && moves[3] == 2){
                sparks();
                moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1;
                EPWM1_LoadDutyValue(0);
                EPWM2_LoadDutyValue(0);
                PWM4_LoadDutyValue(0);
                DELAY_milliseconds(500);
            }
            
            timer++;
            if(timer > 3){
               moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1; 
               timer = 0;
               //SLEEP();
            }
        }else if (mathAbs(data_z) > mathAbs(data_y) + mathAbs(data_x)){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(0); //1
           
            DELAY_milliseconds(100);
            if(part < 4 && moves[part-1] != 3){
                moves[part] = 3;
                part++;   
            }else if(moves[part-1] == 3){
                if(moves[1] == 2 && moves[2] == 3){
                    lumos();
                    moves[1] = 0; moves[2] = 0; part = 1;
                    EPWM1_LoadDutyValue(0);
                    EPWM2_LoadDutyValue(0);
                    PWM4_LoadDutyValue(0);
                    DELAY_milliseconds(500);
                }
            }
            //if(part == 3){
                if(moves[1] == 2 && moves[2] == 1 && moves[3] == 3){
                    patronus();
                    moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1;
                    EPWM1_LoadDutyValue(0);
                    EPWM2_LoadDutyValue(0);
                    PWM4_LoadDutyValue(0);
                    DELAY_milliseconds(500);
                }
            //}
            timer = 0;
        }
        
        /*if(max_data_x + max_data_y + max_data_z < 25){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(0);
            //DELAY_milliseconds(50);
            moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1;
        }else if(max_data_x > max_data_y && max_data_x > max_data_z){
            EPWM1_LoadDutyValue(3); //B
            EPWM2_LoadDutyValue(0); //R
            PWM4_LoadDutyValue(0); //G
            if(part < 4 && moves[part-1] != 1){
                moves[part] = 1;
                part++;   
            }
            //DELAY_milliseconds(20);
        }else if(max_data_y > max_data_x && max_data_y > max_data_z){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(3);
            PWM4_LoadDutyValue(0);
            if(part < 4 && moves[part-1] != 2){
                moves[part] = 2;
                part++;   
            }
            //DELAY_milliseconds(20);
        }else if(max_data_z > max_data_y && max_data_z > max_data_x){
            EPWM1_LoadDutyValue(0);
            EPWM2_LoadDutyValue(0);
            PWM4_LoadDutyValue(3);
            if(part < 4 && moves[part-1] != 3){
                moves[part] = 3;
                part++;   
            }
            //DELAY_milliseconds(20);
        }*/
        /*
        if(moves[1] == 1 && moves[2] == 3 && moves[3] == 1){
            patronus();
            moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1;
        }
         * */

        /*if (data_y > 0)
            EPWM2_LoadDutyValue(data_y);
        else
            EPWM2_LoadDutyValue(data_y * (-1));
        
        if (data_z > 0)
            PWM4_LoadDutyValue(data_z);
        else
            PWM4_LoadDutyValue(data_z * (-1));*/

        previous_data_x = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07);
        previous_data_y = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x09);
        previous_data_z = I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x0B);
        
        //DELAY_milliseconds(10);
        
    }
}

//Wakeup Interrupt handler
void WakeUpInterrupt(void){
    //when accelerometer detects a movement, wake up the MCU
    
    EPWM1_LoadDutyValue(10);
    EPWM2_LoadDutyValue(10); //Red, so reset moves
    PWM4_LoadDutyValue(10);
    
    //if(I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x07)>500){
    //   I2C1_Read1ByteRegister(KXTJ3_I2C_ADDR, 0x1B);   
    //}else{
    //    SLEEP();
    //}
}

//Button Interrupt handler
void ButtonInterrupt(void){
    //moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0; part = 1;
    //patronus(); //test a LED effect when button is pressed
    /*
    EPWM1_LoadDutyValue(11); //B
    EPWM2_LoadDutyValue(120); //R
    PWM4_LoadDutyValue(160);
    DELAY_milliseconds(1000);*/
    
    sparks();
}

//Timer Interrupt handler
void TimerInterrupt(void)
{
    TMR4_StopTimer(); //after timer reaches 0, stop it
}

/**
 End of File
*/