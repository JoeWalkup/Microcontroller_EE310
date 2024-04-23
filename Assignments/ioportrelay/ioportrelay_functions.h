/* 
 * File:   ioportrelay_functions.h
 * Author: us3r
 *
 * Created on April 19, 2024, 9:36 AM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000
#define FCY     _XTAL_FREQ/4

//variables etc.
const char Sevenseg[] __at(0x100) = {0x3f, 0x06, 0x5B, 0x4F, 0x66}; //array of seven segment for 1,2,3,4
int SECRET_CODE = 0x22;
int Sevenseg_counter = 0;
int Cont = 0; //continue button
int Inter = 0; //interrput button
int digit1 = 0;
int digit2 = 0;
int code = 0; //combined code

//interrupt function
void __interrupt(irq(IRQ_INT0), base(0x4008)) INT0_ISR(void)
{
    if(PIR1 == 1){
            PORTDbits.RD7 = 1; //buzzer tone (short beep, long beep, short beep)
            __delay_ms(250);
            PORTDbits.RD7 = 0;
            __delay_ms(100);
             PORTDbits.RD7 = 1;
            __delay_ms(500);
            PORTDbits.RD7 = 0;
            __delay_ms(100);
             PORTDbits.RD7 = 1;
            __delay_ms(250);
            PORTDbits.RD7 = 0;
            __delay_ms(100);
        }
    PIR1 = 0;
}

//monitoring function
void monitor(void){ 
    PORTBbits.RB7 = 1;      // turn on SYS_LED
    PORTBbits.RB0 = 0;      // relay off
    PORTD = Sevenseg[0];
    while(1){
        //first photoresistor check
        if (Cont == 0){
            PORTBbits.RB1 = 1; //activate first photoresistor
            if(PORTBbits.RB2 == 1){
                Sevenseg_counter++;
                PORTD = Sevenseg[Sevenseg_counter];
                __delay_ms(500);
            }
            if (Sevenseg_counter >= 5){
                Sevenseg_counter = 0;
            }
            
            //continue switch check
            if (PORTBbits.RB5 == 1){
            Cont++;
            if(Cont == 1){
                digit1 = Sevenseg_counter - 1;
                __delay_ms(500);
                Sevenseg_counter = 0;
                PORTD = 0;
            }
            if (Cont == 2){
                digit2 = Sevenseg_counter - 1;
            }
            __delay_ms(500);
        }
        }
        
        //second photoresistor check
        if(Cont == 1){ 
            PORTBbits.RB1 = 0;  //deactivate first photoresistor
            PORTBbits.RB3 = 1; //activate second photoresistor
            
            if(PORTBbits.RB4 == 1){
                Sevenseg_counter++;
                PORTD = Sevenseg[Sevenseg_counter];
                __delay_ms(500);
            }
            if (Sevenseg_counter >= 5){
                Sevenseg_counter = 0;
            }
        }
        
        //check if inputed code is same as secret code
        if (Cont == 2){
            
            PORTBbits.RB3 = 0; //deactivate second photoresistor
            code = (digit2*16) | (digit1); //combine digit1 and 2 together into hex number
            
            if (SECRET_CODE == code){
                PORTBbits.RB0 = 1; //turn on relay (motor)
                __delay_ms(2000);
                PORTBbits.RB0 = 0;
                PORTD = 0;
                Sevenseg_counter = 0;
                Cont = 0;
            }
            
            
            else{ //turn on buzzer and reset values
                PORTDbits.RD7 = 1;
                __delay_ms(1500);
                PORTDbits.RD7 = 0;
                PORTDbits.RD7 = 1;
                __delay_ms(100);
                PORTDbits.RD7 = 0;
                PORTD = Sevenseg[0];
                Sevenseg_counter = 0;
                Cont = 0;
            }
    }
    }}
    
