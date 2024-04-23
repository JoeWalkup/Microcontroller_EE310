/* 
 * File:   ioportrelay_Initialization.h
 * Author: Joseph Walkup
 *
 * Created on April 19, 2024, 9:32 AM
 */
#include <xc.h>
void initialize(void){
    PORTD = 0; ANSELD = 0; LATD = 0; TRISD = 0b00000000;
    PORTB = 0; ANSELB = 0; LATB = 0; TRISB = 0b00101110;
    //PORTD 0-6 is output for seven segment and  PORTD 7 is output for buzzer
    //PORTB 0 is output for relay. PORTB 1 is output for first photoresistor
    //and PORTB 2 is input for first photoresistor. PORTB 3 is output for 
    //second photoresistor and PORTB 4 is input for second photoresistor. 
    //PORTB 5 is input for the continue switch and PORTB 6 is input for
    //interrupt switch. Finally, PORTB 7 is output for SYS_LED.
    
    //Enable interrupt priority bit in INTCON0 register
    INTCON0bits.IPEN = 1;
    
    //Enables high priority interrupts
    INTCON0bits.GIEH = 1;
    
    //Enables low priority interrupts
    INTCON0bits.GIEL = 1;
    
    //INterrupt on rising edge  of INT0 pin
    INTCON0bits.INT0EDG = 0;
    
    //Sets the interrupt high priority (IP) for INT0 - INT0IP
    IPR1bits.INT0IP = 1;
    
    //Enable the interrupt (IE) for INT0
    PIE1bits.INT0IE = 1;
    
    //Clears interrupt flag for INT0
    PIR1bits.INT0IF = 1;
    
    IVTBASEU = 0x00;
    IVTBASEH = 0x40;
    IVTBASEL = 0x08;
    
    return;
}
