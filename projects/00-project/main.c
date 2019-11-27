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
#include <stdlib.h>         // itoa() function
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define IR_LED_PIN       PB2
#define IR_SENSOR_PIN    PB1
#define USENSOR_ECHO_PIN PB3
#define USENSOR_TRIG_PIN PB4

#define UART_BAUD_RATE 9600

#define ANSI_UART_C_NORMAL uart_puts("\033[0m")
#define ANSI_UART_C_YELLOW uart_puts("\e[33m")
#define ANSI_UART_C_RED    uart_puts("\e[31m")
#define ANSI_UART_C_GREEN  uart_puts("\e[92m")
#define ANSI_UART_C_BLUE   uart_puts("\e[34m")
#define ANSI_UART_C_CYAN   uart_puts("\e[96m")
#define ANSI_UART_C_MAGENTA uart_puts("\e[35m")
#define ANSI_UART_C_BLINK uart_puts("\e[5m")
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
void USensorTrigger();
/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void) {
    
    // UART: asynchronous,
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    /* Set output pin */
    GPIO_config_output(&DDRB,IR_LED_PIN);
    GPIO_config_output(&DDRB,USENSOR_TRIG_PIN);    

    /* Set input pin */
    GPIO_config_input_pullup(&DDRB,&PORTB,IR_SENSOR_PIN);
    GPIO_config_input_nopull(&DDRB,&PORTB,USENSOR_ECHO_PIN);

    /* Turn LED off */
    GPIO_write(&PORTB,IR_LED_PIN,0);   
    GPIO_write(&PORTB,USENSOR_TRIG_PIN,0); 
    
    // Timer 1
    TIM_config_prescaler(TIM0, TIM_PRESC_1); 
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    sei();
    
    // Put strings to ringbuffer for transmitting via UART.
    uart_puts("IR senzory\n");
      
    /* Infinite loop */
    for (;;) {
      if(GPIO_read(&PINB,IR_SENSOR_PIN)) {
        ANSI_UART_C_RED; // vstup 1
        uart_puts("X");
        ANSI_UART_C_NORMAL;
      }
      else {
        ANSI_UART_C_GREEN; // vstup 0
        uart_puts("X");
        ANSI_UART_C_NORMAL;
      }
      _delay_ms(50);
    }

    return (0);
}

ISR(TIMER0_OVF_vect) {
        /* Invert LED and delay */
        GPIO_toggle(&PORTB,IR_LED_PIN);
}

void USensorTrigger() {
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,1); 
  _delay_us(5);
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,0); 
}
