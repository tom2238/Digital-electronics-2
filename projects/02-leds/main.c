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
    DDRB |= _BV(LED_PIN1);           /* DDRB = DDRB or (0010 0000) */
    DDRB |= _BV(LED_PIN2);
    DDRB &= ~_BV(button_PIN1);

    /* Turn LED off */
    PORTB &= ~_BV(LED_PIN1);         /* PORTB = PORTB and (0010 0000) */
    PORTB &= ~_BV(LED_PIN2);
    PORTB |= _BV(button_PIN1);    
    /* Infinite loop */
    
    for (;;)
    {
        if (bit_is_set(PINB , button_PIN1)) 
        {
          PORTB ^= _BV(LED_PIN2); 
                _delay_us(BLINK_DELAY);   
          PORTB ^= _BV(LED_PIN1);    
        }   
    }

    return (0);
}

/*  
        if (bit_is_set(PINB , button_PIN1)) {
          PORTB ^= _BV(LED_PIN2);      
        } 
*/
/*   prepinani
        loop_until_bit_is_clear(PINB , button_PIN1);
      PORTB ^= _BV(LED_PIN2);
      PORTB ^= _BV(LED_PIN1);

        loop_until_bit_is_set(PINB , button_PIN1);     

        _delay_us(BLINK_DELAY);    
*/