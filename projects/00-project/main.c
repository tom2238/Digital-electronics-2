/*
 * ---------------------------------------------------------------------
 * Author:      Milan Hornik, Tomas Dubina
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-20
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Racing car, Track time and round measurements.
 * Main source file
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "main.h"
#include "timer.h"
#include "uart.h"
#include "gpio.h"
#include "hcsr04.h"


/* Variables */
/* Function prototypes */

void GPIOInit();
void UARTInit();
void TimerInit();

/* Functions */

/**
  * Brief:  Main program.
  * Input:  None
  * Return: None
  */

int main(void) {
  UARTInit();
  GPIOInit();
  TimerInit();

  // Put strings to ringbuffer for transmitting via UART.
  uart_puts("Autodraha pripravena\n");
      
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

  return 0;
}

ISR(TIMER0_OVF_vect) {
  /* Invert LED and delay */
  GPIO_toggle(&PORTB,IR_LED_PIN);
}

void GPIOInit() {
  /* Set output pins */
  GPIO_config_output(&DDRB,IR_LED_PIN);
  GPIO_config_output(&DDRB,USENSOR_TRIG_PIN);

  /* Set input pins */
  GPIO_config_input_pullup(&DDRB,&PORTB,IR_SENSOR_PIN);
  GPIO_config_input_nopull(&DDRB,&PORTB,USENSOR_ECHO_PIN);

  /* Turn outputs off */
  GPIO_write(&PORTB,IR_LED_PIN,0);
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,0);
}

void UARTInit() {
  // UART: asynchronous,
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
}

void TimerInit() {
  // Timer 1
  TIM_config_prescaler(TIM0, TIM_PRESC_1);
  TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

  sei();
}
