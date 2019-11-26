/*
 * ---------------------------------------------------------------------
 * Author:      Milan Hornik, Tomas Dubina
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN1     PB5
#define LED_PIN2     PB0
#define BLINK_DELAY 400000
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
    DDRB |= _BV(LED_PIN1);           /* DDRB = DDRB or (0010 0000) */
    DDRB |= _BV(LED_PIN2);

    /* Turn LED off */
    PORTB &= ~_BV(LED_PIN1);         /* PORTB = PORTB and (0010 0000) */
    PORTB &= ~_BV(LED_PIN2);
    /* Infinite loop */
    for (;;)
    {
        /* Invert LED and delay */
        PORTB ^= _BV(LED_PIN1);      /* PORTB = PORTB xor (0010 0000) */
        _delay_us(BLINK_DELAY);     /* Wait for several milisecs */
        PORTB ^= _BV(LED_PIN2);      /* PORTB = PORTB xor (0010 0000) */
        _delay_us(BLINK_DELAY);     /* Wait for several milisecs */
    }

    return (0);
}
