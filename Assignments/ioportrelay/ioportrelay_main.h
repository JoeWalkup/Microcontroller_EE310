/* -------------------------
 *  File:   ioportrelay_main.h
 * -------------------------
 * Dependencies: IOHeader.h, IO_innit.h, IOfunctions.h
 * Compiler: MPLAB X IDE v6.20:XC8(v2.46)
 * Author: Joseph Walkup
 * Outputs: PORTD, PORTB(0,1,3,7)
 * Inputs: PORTB(2,4,5,6)
 * Versions:
 *  V1.0: 04/19/2024
 */

#include "headerfile.h"
#include "ioportrelay_functions.h"
#include "ioportrelay_Initialization.h"
#include <xc.h>

#define _XTAL_FREQ 4000000
#define FCY     _XTAL_FREQ/4

void initialize(void);
void monitor(void);

void main(void) {
    initialize();
    monitor();
    return;
}
