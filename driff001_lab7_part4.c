/*	Author: Dylan Riffel
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab 7  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * Video Link: https://www.youtube.com/watch?v=kwSOrCvgXSM 
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
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    unsigned short my_short = 0xABCD;
    unsigned char my_char;
   
    ADC_init();
    /* Insert your solution below */
    while (1) {
    my_short = ADC;
    my_char = my_short;
    if( my_char >= 0b1000000 && my_char <= (0b1111111)){
    PORTB = 0b11111111;
    }
    else if( my_char >= 0b100000 && my_char <= (0b111111)){
    PORTB = 0b1111111;
    }
    else if( my_char >= 0b100000 && my_char <= (0b111111)){
    PORTB = 0b111111;
    }
    else if( my_char >= 0b10000 && my_char <= (0b11111)){
    PORTB = 0b11111;
    }
    else if( my_char >= 0b1000 && my_char <= (0b1111)){
    PORTB = 0b1111;
    }
    else if( my_char >= 0b100 && my_char <= (0b111)){
    PORTB = 0b111;
    }
    else if( my_char >= 0b10 && my_char <= (0b11)){
    PORTB = 0b11;
    }

    else {
    PORTB = 0b01;
    }	    

    }
    return 1;
}
