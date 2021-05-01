/*	Author: Dylan Riffel
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab 7  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *  Video Link: https://www.youtube.com/watch?v=bz1v6trRhdc
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init(){
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}



int main(void) {
    /* Insert DDR and PORT initializations */
    PINA = 0xFF;
    unsigned short my_short = 0xABCD;
    unsigned char my_char;
    unsigned char my_char2; 
    ADC_init();
    /* Insert your solution below */
    while (1) {
    my_short = ADC;
    my_char = my_short >> 8 ;
    my_char2 = my_short & 0b0011111111;
    PORTB = my_char2;
    PORTD = my_char;

    }
    return 1;
}
