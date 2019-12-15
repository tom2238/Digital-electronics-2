#include <avr/interrupt.h>
#include "main.h"
#include "initall.h"
#include "gpio.h"
#include "timer.h"
#include "nokia5110.h"
#include "uart.h"

void GPIOInit() {
  /* Set output pins */
  GPIO_config_output(&DDRB,IR_LED_PIN);
  GPIO_config_output(&DDRD,USENSOR_TRIG_PIN);
  GPIO_config_output(&DDRD,USENSOR_TRIG_PIN_2);

  /* Set input pins */
  GPIO_config_input_nopull(&DDRB,&PORTB,IR_SENSOR_PIN);
  GPIO_config_input_nopull(&DDRD,&PORTD,USENSOR_ECHO_PIN);
  GPIO_config_input_nopull(&DDRD,&PORTD,USENSOR_ECHO_PIN_2);

  /* Turn outputs off */
  GPIO_write(&PORTB,IR_LED_PIN,HIGH);
  GPIO_write(&PORTD,USENSOR_TRIG_PIN,LOW);
  GPIO_write(&PORTD,USENSOR_TRIG_PIN_2,LOW);
}

void UARTInit() {
  // UART: asynchronous,
  #ifdef UART_DEBUG
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  #endif
}

void TimerInit() {
  // Timer 0 nutne pro funkci millis();
  TIM_config_prescaler(TIM0, TIM_PRESC_64); // Millis() function
  TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
  sei(); //Enable global interrupts
}

void NokiaLCDInit() {
  nokia_lcd_init();
  nokia_lcd_clear();
  nokia_lcd_write_string("[*>#]Test{i8$}",1);
  nokia_lcd_set_cursor(0, 10);
  nokia_lcd_render();
}

void ObjectsInit() {
  auto1 = ClearCar(auto1);
  auto2 = ClearCar(auto2);
}
