//-----------------------------
// Title: Ass_Counter.asm
//-----------------------------
// Purpose: Depending on the switch, A and B, the 7 segment will 
   //count up or down from 0 to F. If both are pressed then it 
   //goes to 0 and if none it stays at the value it is.
// Dependencies: headerfile.inc
// Compiler: MPLAB X IDE v6.20 - pic-as (v2.46)
// Author: Joseph Walkup
// OUTPUTS: 7 segment display which is connected to PortD
// INPUTS: Switch A is RB0 and Switch B is RB1 
// Versions:
//  	V1.0: 3/26/24 
//-----------------------------

#include "./headerfile.inc"
#include <xc.inc>
    PSECT absdata,abs,ovrld
//----------------
    //initialize ports
 //PORTB to input. Switch A = RB0 and Switch B = RB1
    BANKSEL	PORTD ;
    CLRF	PORTD ;Init PORTA
    BANKSEL	LATD ;Data Latch
    CLRF	LATD ;
    BANKSEL	ANSELD ;
    CLRF	ANSELD ;digital I/O
    BANKSEL	TRISD ;
    MOVLW	0b00000000 ;Set RD[7:1] as outputs
    MOVWF	TRISD ;and set RD0 as ouput
    
    BANKSEL	PORTB ;
    CLRF	PORTB ;Init PORTB
    BANKSEL	LATB ;Data Latch
    CLRF	LATB ;
    BANKSEL	ANSELB ;
    CLRF	ANSELB ;digital I/O
    BANKSEL	TRISB ;
    MOVLW	0b11111111 ;
    MOVWF	TRISB ;
    //display states
    MOVLW   0b00111111
    MOVWF   0x4F,0 //0
    MOVLW   0b00111111
    MOVWF   0x50,0 //0
    MOVLW   0b00110000
    MOVWF   0x51,0 //1
    MOVLW   0b01011001
    MOVWF   0x52,0 //2
    MOVLW   0b01001111
    MOVWF   0x53,0 //3
    MOVLW   0b01100110
    MOVWF   0x54,0 //4
    MOVLW   0b01101101
    MOVWF   0x55,0 //5
    MOVLW   0b01111101
    MOVWF   0x56,0 //6
    MOVLW   0b00000111
    MOVWF   0x57,0 //7
    MOVLW   0b01111111
    MOVWF   0x58,0 //8
    MOVLW   0b01101111
    MOVWF   0x59,0 //9
    MOVLW   0b01110111
    MOVWF   0x5A,0 //A
    MOVLW   0b01111100
    MOVWF   0x5B,0 //B
    MOVLW   0b01011000
    MOVWF   0x5C,0 //C
    MOVLW   0b01011110
    MOVWF   0x5D,0 //D
    MOVLW   0b01111001
    MOVWF   0x5E,0 //E
    MOVLW   0b01110001
    MOVWF   0x5F,0 //F
    LFSR    0,0x50
    MOVFF   INDF0,PORTD
//----------------Main
Start:
    CALL    Delay
    MOVLW   0b00000001 //switch A on
    CPFSEQ  PORTB,0
    GOTO    skip1
    CALL    CountUp
    GOTO    Start
skip1:
    MOVLW   0b00000010 //switch B on
    CPFSEQ  PORTB,0
    GOTO    skip2
    CALL    CountDown
    GOTO    Start
skip2:
    MOVLW   0b00000011 //both on
    CPFSEQ  PORTB,0
    GOTO    Start
    LFSR    0,0x50 //reset to 0
    MOVFF   INDF0,PORTD
    GOTO    Start
    SLEEP
    
//----------------functions
    //Delay
Delay:
    MOVLW   10 //# of loops for loop 1
    MOVWF   0x10,0 //loop1 reg
    MOVLW   2 //# of loops for loop2
loop1:
    MOVWF   0x11,0 //loop2 reg
    DECFSZ  0x10,1,0
    GOTO    loop2
    GOTO    out2
loop2:
    DecFSZ  0x11,1,0
    GOTO    loop2
    GOTO    loop1
out2:
    return
    //CountUp
CountUp:
    MOVLW   0b01110001
    CPFSEQ  LATD,0
    GOTO    jump1
    LFSR    0,0x50
    MOVFF   INDF0,PORTD
    return
jump1:
    MOVFF   PREINC0,PORTD
    return
    //CountDown
CountDown:
    MOVLW   0b00111111
    CPFSEQ  LATD,0
    GOTO    jump2
    LFSR    0,0x5F
    MOVFF   INDF0,PORTD
    return
jump2:
    MOVFF   POSTDEC0,PORTD
    return


