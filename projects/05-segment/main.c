/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    GPIO_config_output(&DDRB,LED_D1);

    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9
    PCMSK1 |= _BV(PCINT9) | _BV(PCINT10) | _BV(PCINT11); 
    PCICR  |= _BV(PCIE1);

    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    GPIO_config_output(&DDRB,SEGMENT_DATA);
    GPIO_config_output(&DDRD,SEGMENT_CLK);
    GPIO_config_output(&DDRD,SEGMENT_LATCH);

    /* Enable interrupts by setting the global interrupt mask */
    sei();
    
    uint8_t num1=0;
    /* Infinite loop */
    for (;;) {
        // TODO: Use function to display digit 1 at position 0
        
        /*
        for(i=0;i<2000;i++) {
        SEG_putc(9, 3);
        SEG_putc(8, 2);
        SEG_putc(7, 1);
        SEG_putc(6, 0);
        //_delay_ms(1);
        }
        for(i=0;i<2000;i++) {
        SEG_putc(5, 3);
        SEG_putc(4, 2);
        SEG_putc(3, 1);
        SEG_putc(2, 0);
        //_delay_ms(1);
        }
        */
        /*  counter 0-9
        for(i=0;i<10;i++)
        {
        SEG_putc(i, 0);
        _delay_ms(500);
        }
        */
        if(num1>100) {
          num1=0;
        }
        SEG_putc(num1 % 10, 0);
        _delay_ms(10);
        SEG_putc(num1/10, 1);
        num1++;
        _delay_ms(10);
        
    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */
ISR(PCINT1_vect)
{
    // TODO: Toggle a led
    GPIO_toggle(&PORTB,LED_D1);
}
