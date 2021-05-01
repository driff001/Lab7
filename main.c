/*	Author: dylan
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include <avr/interrupt.h>
#include "simAVRHeader.h"
#endif


volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
int count = 0;
int count2 = 0;

void TimerOn(){
TCCR1B = 0x0B;
OCR1A = 125;
TIMSK1 = 0x02;
TCNT1 = 0;
_avr_timer_cntcurr = _avr_timer_M;
SREG |= 0x80;

}	

void TimerOff(){
TCCR1B = 0x00;
}	
void TimerISR(){
TimerFlag = 1;
}	
ISR(TIMER1_COMPA_vect){

    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0){
	TimerISR();
	_avr_timer_cntcurr = _avr_timer_M;
    
    }	    
}



void TimerSet(unsigned long M){
       _avr_timer_M = M;
       _avr_timer_cntcurr = _avr_timer_M;
}	

enum S_STATES { S_Wait, S_Press1, S_Press2,S_Press3,S_PressWait1, S_PressWait2,S_PressWait3} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    case S_Wait: //wait state
        if(255 - PINA == 0b00){
            S_State = S_Wait;
        }
        else if(255 - PINA == 0x01){
            S_State = S_Press1;
        }
        else if(255 - PINA == 0x02){
            S_State = S_Press2;
        }
        else{
            S_State = S_Press3;
        }
        S_State = (255 - PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press1: //increment state
        if(255 - PINA == 0b00){
          S_State = S_Wait;
        }
        else if (255 - PINA == 0b01){
         
          S_State = S_PressWait3;
        }
        else if(255 - PINA == 0x02){
          S_State = S_Press2;
        }
        S_State = (255 - PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press2: //decrement state
        if(255 - PINA == 0b00){
        S_State = S_Wait;
        }
        else if (255 - PINA == 0b10){
          S_State = S_PressWait3;
        }

        else if(255 - PINA == 0x01){
          S_State = S_Press1;
        }
        S_State = (255 - PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press3: //increment state
        if(255 - PINA == 0b00){
            S_State = S_Wait;
        }
        else if(255 - PINA == 0x01){
            S_State = S_Press1;
        }
        else if(255 - PINA == 0x02){
            S_State = S_Press2;
        }
        else{
            S_State = S_Wait;
        }
        break;

    case S_PressWait1: 
        if (255 - PINA == 0b00){
          S_State = S_Wait;
        }
        else if(255 - PINA == 0x02){
          S_State = S_Press2;
        }
        else{
          S_State = S_PressWait1;
        }
        S_State = (255 - PINA == 0x03)? S_Press3 : S_State;
        break;
    case S_PressWait2:
	
        if (255 - PINA == 0b00){
          S_State = S_Wait;
        }
        else if(255 - PINA == 0x01){
          S_State = S_Press1;
        }
        else{
          S_State = S_PressWait2;
        }
        S_State = (255 - PINA == 0x03)? S_Press3 : S_State;
        break;
   
    case S_PressWait3:
       ++count2;
       if((255 - PINA == 0b01) && count2 == 10){
       count2 = 0;
       PORTB += 1;
       }       
       else if ( (255 - PINA == 0b10) && count2 == 10){
       count2 = 0;
       PORTB -= 1;
       }
       else{
       S_State = S_PressWait3;
       }
       break;
   }
   switch(S_State) //State actions
   {
      case S_Press1:
        if (PORTB < 0x09){
        PORTB += 1;
        }
        PORTB = PORTB;
        break;

      case S_Wait: //wait state
        break;

      case S_Press2: //incrment state
        if (PORTB > 0){
        PORTB -= 0b01;
        }
        PORTB = PORTB;
        break;
      case S_Press3: //incrment state
        if (255-PINA == 0b11){
        PORTB = 0b00;
        }
        break; 

      case S_PressWait1:
        break;

      case S_PressWait2:
        break;
      case S_PressWait3:
	break;
   }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTA = 0xFF;
    PORTB = 0b111;
    TimerSet(100);
    S_State = S_Wait;
    TimerOn();
    /* Insert your solution below */
    while (1) {
    Tick();
   

    while(!TimerFlag);
    TimerFlag = 0;

    }
    
}
