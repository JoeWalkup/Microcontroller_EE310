//-----------------------------
// Title: Calcmain.c
//-----------------------------
// Purpose: A simple calculator that can add, subtract, multiply, and divide two numbers.
//The numbers can be from 1 to 9. The user presses the first number they want, then they 
//press an operation key. Finally, they press the last digit they want and the pound sign
// the 8 leds will display the binary representation of the answer.
// Dependencies: headerfile.h
// Compiler: MPLAB X IDE v6.20 - XC8 (v2.46)
// Author: Joseph Walkup
// OUTPUTS: PORTD, PORTB.0, PORTB.1, PORTB.2, and PORTB.5
// INPUTS: PORTB.3, PORTB.4, PORTB.6, and PORTB.7
// Versions:
//  	V1.0: 4/6/24 
//-----------------------------



#include <xc.h> 
#include "./headerfile.h"
#define _XTAL_FREQ 4000000
#define FCY     _XTAL_FREQ/4


int Operation (int);
int Input (int);
int Addition_OP(int, int);
int Subtraction_OP(int, int);
int Multiplication_OP(int, int);
int Division_OP(int, int);
void Delay(unsigned int, unsigned int);


char Operation_REG;
int X_Input_REG;
int Y_Input_REG;
int Display_Result_REG;
int Op_intermediate;


void main (void)
{
    //set PORTD as output
    PORTD = 0;
    LATD = 0;
    ANSELD = 0;
    TRISD = 0;
    //set PORTB.3,4,6,7 as input and PORTB.0,1,2,5 as output
    PORTB = 0;
    LATB = 0;
    ANSELB = 0;
    TRISB = 0xD8; //0b11011000

    //set counters and input regs as 0
    Op_intermediate = 0;
    X_Input_REG = 0;
    Y_Input_REG = 0;
    Operation_REG = 0;
    Display_Result_REG = 0;
    
    while(1){
        
        //check and set first number (x input))
        if (PORTD == 0){
            X_Input_REG = Input(X_Input_REG);
            if (X_Input_REG > 0){
                PORTD = 1;
            }
        }
        
        //check and set operation
         if (PORTD == 1){
            Operation_REG = Operation(Operation_REG);
            Op_intermediate = Operation_REG; 
        }
        
        if (Op_intermediate > 0){
            PORTD = 3;
            Op_intermediate = 0;
        }
       
        //check and set second number (y input)
        if (PORTD == 3){
            Y_Input_REG = Input(Y_Input_REG);
            if (Y_Input_REG > 0){
                PORTD = 2;
            }
        }
            
        //check which operation function to use and compute value
        if (PORTD == 2){
            if (Operation_REG == 1){
                Display_Result_REG = Addition_OP(X_Input_REG, Y_Input_REG);
            }
            else if (Operation_REG == 2){
                Display_Result_REG = Subtraction_OP(X_Input_REG, Y_Input_REG);
            }
            else if (Operation_REG == 3){
                Display_Result_REG = Multiplication_OP(X_Input_REG, Y_Input_REG);
            }
            else if (Operation_REG == 4){
                Display_Result_REG = Division_OP(X_Input_REG, Y_Input_REG);
            }
        }
           
            if (PORTD == 2){
                PORTBbits.RB2 = 1;
                if (PORTBbits.RB6 == 1){
                    PORTD = Display_Result_REG;
                }
                PORTBbits.RB2 = 0;
            }
        
            
    
        
        //reset calc
        if (PORTD != 0){
                PORTBbits.RB1 = 1;
                if (PORTBbits.RB6 == 1){
                    PORTD = 0;
                    X_Input_REG = 0;
                    Y_Input_REG = 0;
                    Operation_REG = 0;
                }
                PORTBbits.RB1 = 0;
            }
        //Delay(100,100);
    }
    }  
        

//operation check function
int Operation(int x1){
    x1 = 0;
    PORTBbits.RB5 = 1; //check only letter column
    if (PORTBbits.RB3 == 1) //add op row (A)
        x1 = 1; 
    else if (PORTBbits.RB4 == 1) //sub op row (B)
        x1 = 2; 
    else if (PORTBbits.RB7 == 1) //mul op row (C)
        x1 = 3; 
    else if (PORTBbits.RB6 == 1) //div op row (D)
        x1 = 4;
    PORTBbits.RB5 = 0; //stop checking letter column
    return x1;
}
//input check function
int Input(int x2){
    x2 = 0;
 
    PORTBbits.RB0 = 1; //checking first column
    if (PORTBbits.RB3 == 1) //check first row
        x2 = 1;
    else if (PORTBbits.RB4 == 1) //check second row
        x2 = 4;
    else if (PORTBbits.RB7 == 1) //check third row
        x2 = 7;
    PORTBbits.RB0 = 0; //stop checking first column
        
        

    PORTBbits.RB1 = 1; //checking second column
    if (PORTBbits.RB3 == 1)
        x2 = 2;
    else if (PORTBbits.RB4 == 1)
        x2 = 5;
    else if (PORTBbits.RB7 == 1)
        x2 = 8;
    PORTBbits.RB1 = 0;
        
        

    PORTBbits.RB2 = 1; //checking third column
    if (PORTBbits.RB3 == 1)
        x2 = 3;
    else if (PORTBbits.RB4 == 1)
        x2 = 6;
    else if (PORTBbits.RB7 == 1)
        x2 = 9;
    PORTBbits.RB2 = 0;
        
    return x2;
}

//addition function
int Addition_OP (int X3, int Y3)
{
    int Add;
    Add = X3 + Y3;
    return Add;
}


//subtraction function
int Subtraction_OP (int X4, int Y4)
{
    int Sub;
    Sub = X4 - Y4;
    return Sub;
}


// multiplication function
int Multiplication_OP (int X5, int Y5)
{
    int Mul;
    Mul = X5 * Y5;
    return Mul;
}


// division function
int Division_OP (int X6, int Y6)
{
    int Div;
    Div = X6 / Y6;
    return Div;
}

//delay function
void Delay(unsigned int loop1, unsigned int loop2)
{
    
    unsigned int i; unsigned int j;
    for (i = 0; i < loop1 ;  i++)
        for (j = 0 ; j< loop2 ; j++);
}    
