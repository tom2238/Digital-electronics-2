#include <avr/interrupt.h>
#include "main.h"
#include "initall.h"
#include "gpio.h"
#include "timer.h"
#include "nokia5110.h"

void GPIOInit() {
  /* Set output pins */
  GPIO_config_output(&DDRB,IR_LED_PIN);
  GPIO_config_output(&DDRD,USENSOR_TRIG_PIN);
  GPIO_config_output(&DDRD,USENSOR_TRIG_PIN_2);

  /* Set input pins */
  GPIO_config_input_nopull(&DDRB,&PORTB,IR_SENSOR_PIN);
  GPIO_config_input_pullup(&DDRD,&PORTD,USENSOR_ECHO_PIN);
  GPIO_config_input_pullup(&DDRD,&PORTD,USENSOR_ECHO_PIN_2);

  /* Turn outputs off */
  GPIO_write(&PORTB,IR_LED_PIN,LOW);
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
  // Timer 0
  TIM_config_prescaler(TIM0, TIM_PRESC_64); // Millis() functions
  TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
  // Pin change interrups HC-SR04 echo pin
  PCICR |= _BV(PCIE2);
  PCMSK2 |= _BV(PCINT18); // echo 1
  PCMSK2 |= _BV(PCINT20); // echo 2
  sei(); //Enable global interrupts
}

void NokiaLCDInit() {
  nokia_lcd_init();
  nokia_lcd_clear();
  nokia_lcd_write_string("[*>#] Test LCD!!!",1);
  nokia_lcd_set_cursor(0, 10);
  nokia_lcd_render();
}

void PWMInit() {
  DDRB |= (1 << PINB1);
  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Mode: Fast PWM
  // Input Capture on Falling Edge
  TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10);
  TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
  TCNT1H=0x00;
  TCNT1L=0x00;
}

void ObjectsInit() {
  auto1 = ClearCarTime(auto1);
  distance.enable = FALSE;
  distance.complete = TRUE;
  distance.pulses = 0;
  distance2.enable = FALSE;
  distance2.complete = TRUE;
  distance2.pulses = 0;
}
