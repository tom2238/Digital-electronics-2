/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "gpio.h"
#include "timer.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN1     PB5
#define LED_PIN2     PB0
#define button_PIN1     PB2
#define BLINK_DELAY 200000
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    
    /* Set output pin */
    //DDRB |= _BV(LED_PIN1);           /* DDRB = DDRB or (0010 0000) */
    //DDRB |= _BV(LED_PIN2);

    GPIO_config_output(&DDRB,LED_PIN1);
    GPIO_config_output(&DDRB,LED_PIN2);
    GPIO_config_input_pullup(&DDRB,&PORTB,button_PIN1);

    /* Turn LED off */
    //PORTB &= ~_BV(LED_PIN1);         /* PORTB = PORTB and (0010 0000) */
    //PORTB &= ~_BV(LED_PIN2);
    GPIO_write(&PORTB,LED_PIN1,0);
    GPIO_write(&PORTB,LED_PIN2,0);

    /* Set Timer0 */
    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    /* Set Timer1 */
    // TODO: Configure Timer1 clock source and enable overflow interrupt
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    /* Set Timer2 */
    // TODO: Configure Timer2 clock source and enable overflow interrupt
    TIM_config_prescaler(TIM2, TIM_PRESC_1024);
    TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);
    /* Enable interrupts by setting the global interrupt mask */
    sei();
    /* Infinite loop */
    for (;;)
    {
        _delay_ms(1000);
    }

    return (0);
}

/**
 *  Brief: Timer/Counter0 overflow interrupt routine. Toggle green LED.
 */
ISR(TIMER0_OVF_vect)
{
    // TODO: Toggle green LED
    GPIO_toggle(&PORTB,LED_PIN1);
}

/**
 *  Brief: Timer/Counter1 overflow interrupt routine. Toggle blue LED.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Toggle blue LED
    GPIO_toggle(&PORTB,LED_PIN2);
}


/**
 *  Brief: Timer/Counter2 overflow interrupt routine. Toggle red LED.
 */
ISR(TIMER2_OVF_vect)
{
    // TODO: Toggle red LED
   // GPIO_toggle(&PORTB,LED_PIN2);
}
