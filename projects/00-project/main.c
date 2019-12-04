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
#include "nokia5110.h"

/* Function prototypes */

void GPIOInit();
void UARTInit();
void TimerInit();
void PWMInit();
void FrequencyPWM(uint16_t frequency, uint8_t percentage);
void SendIR();
/* Functions */

/**
 * @author Milan Horník, Tomáš Dubina
 * @brief Hlavní program
 * @param  Nic
 * @return Návratový kod
 */
int main(void) {
  GPIOInit();
  UARTInit();
  TimerInit();
  PWMInit();
  nokia_lcd_init();                               
  nokia_lcd_clear();
  distance.enable = FALSE;
  distance.complete = TRUE;
  distance.pulses = 0;
  nokia_lcd_write_string("IT'S WORKING!",1);
  nokia_lcd_set_cursor(0, 10);
  nokia_lcd_render();
  _delay_ms(500);
  uart_puts("Autodraha pripravena\n");

  /* Infinite loop */
  for (;;) {
    /*if(GPIO_read(&PINB,IR_SENSOR_PIN)) {
      ANSI_UART_C_RED; // vstup 1
      uart_puts("X");FALSE
      ANSI_UART_C_NORMAL;
    }
    else {
      ANSI_UART_C_GREEN; // vstup 0
      uart_puts("X");
      ANSI_UART_C_NORMAL;
    }*/
    SendIR();
    /*if(distance.complete) {
        char dist[8];
        itoa(UPulsesToMilimeters(distance.pulses), dist , 10);
        uart_puts(dist);
        uart_puts("||");

    }*/


    /*char dist[8];
    itoa(distance.pulses, dist , 10);
    uart_puts(dist);
    uart_puts("||");*/
    USensorTrigger();
    _delay_ms(100);
  }

  return 0;
}

/**
 * @author Milan Horník
 * @brief Počítá impulzy pokud HC-SR04 vyšle echo, 1 implulz <=> 16 us
 * @param Nic
 * @return Nic
 */
ISR(TIMER0_OVF_vect) {
  // Add
  if(distance.enable) {
    distance.pulses++;
  }
}

/**
 * @author Tomáš Dubina
 * @brief Přerušení pokud dojde ke změně hodnoty na echo pinu PD2
 * @param Nic
 * @return NicFunkce od vektoru přerušení čítače/časovače 0
 */
ISR(PCINT2_vect) {
  if(distance.enable) {
    uart_puts("Zmena|");
    if(distance.pulses > 30) {
      distance.enable = FALSE;
      if(distance.pulses > 700) {
        distance.pulses = 700;
      }


      char dist[8];
      itoa(distance.pulses, dist, 10);
      uart_puts(dist);
      uart_puts("p|");
      nokia_lcd_set_cursor(0,8);
      nokia_lcd_write_string(dist,1);
      uint16_t milimeters = UPulsesToMilimeters(distance.pulses);
      nokia_lcd_write_string(" pulse    ",1);
      itoa(milimeters, dist , 10);
      uart_puts(dist);
      uart_puts(" mm \n");
      nokia_lcd_set_cursor(0,0);
      nokia_lcd_write_string(dist,1);
      nokia_lcd_write_string(" mm       ",1);    
      if ((milimeters>30)&&(milimeters<100)) 
        {
        nokia_lcd_set_cursor(0,16);
        nokia_lcd_write_string(">auto 1    ",1);

        }
      else if ((milimeters>110)&&(milimeters<200))
        {
        nokia_lcd_set_cursor(0,16);
        nokia_lcd_write_string(">auto 2    ",1);
        }
      else
        {
        nokia_lcd_set_cursor(0,16);
        nokia_lcd_write_string(">?????    ",1);
        }
      nokia_lcd_render();
      distance.complete = TRUE;

    }
  }
}

/**
 * @author Milan Horník
 * @brief Inicializace vstupních a výstupních pinů
 * @param Nic
 * @return Nic
 */
void GPIOInit() {
  /* Set output pins */
  GPIO_config_output(&DDRB,IR_LED_PIN);
  GPIO_config_output(&DDRD,USENSOR_TRIG_PIN);

  /* Set input pins */
  GPIO_config_input_pullup(&DDRB,&PORTB,IR_SENSOR_PIN);
  GPIO_config_input_pullup(&DDRD,&PORTD,USENSOR_ECHO_PIN);

  /* Turn outputs off */
  GPIO_write(&PORTB,IR_LED_PIN,0);
  GPIO_write(&PORTD,USENSOR_TRIG_PIN,0);
}

/**
 * @author Milan Horník
 * @brief Inicializace UART rozhraní
 * @param Nic
 * @return Nic
 */
void UARTInit() {
  // UART: asynchronous,
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
}

/**
 * @author Tomáš Dubina
 * @brief Inicializace čítače/časovače 0
 * @param Nic
 * @return Nic
 */
void TimerInit() {
  // Timer 0
  TIM_config_prescaler(TIM0, TIM_PRESC_1);
  TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
  // Pin change interrups
  PCICR |= _BV(PCIE2);
  PCMSK2 |= _BV(PCINT18);
  sei(); //Enable global interrupts
}

/**
 * @author Tomáš Dubina
 * @brief Nastaví frekvenci a střídu PWM
 * @param frequency frekvence PWM v Hz
 * @param percentage střída v %
 * @return Nic
 */
void FrequencyPWM(uint16_t frequency, uint8_t percentage) {
	uint16_t TOP = F_CPU/(PWM_DIVIDER*frequency) - 1;
	ICR1H = TOP >> 8;
	ICR1L = TOP & 0xFF;
    if(percentage > 100) {
      percentage = 100;
    }
    uint16_t OCR = (uint16_t)(((uint32_t)percentage * (uint32_t)TOP)/100);
	OCR1AH = OCR >> 8;
	OCR1AL = OCR & 0xFF;
}

/**
 * @author Tomáš Dubina
 * @brief Inicializace PWM na čítači/časovači 1
 * @param Nic
 * @return Nic
 */
void PWMInit() {
	DDRB |= (1 << PINB1);
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 16 MHz
	// Mode: Fast PWM top=ICR1
	// OC1A output: Non-Inverted PWM
	// OC1B output: Non-Inverted PWM
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 1 s
    // Output Pulse(s):
	// OC1A Period: 1 s Width: 0.2 s
	// OC1B Period: 1 s Width: 0.40001 s
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
}

// NEC protocol
/**
 * @author Tomáš Dubina
 * @brief Trvale posílá sekvenci 8 nul a 8 jedniček
 * @param Nic
 * @return Nic
 */
void SendIR() {
  //Send 1
  uint8_t i;
  for(i=0;i<8;i++) {
    PWM_START;
    _delay_us(IR_PULSE_LEN);
    PWM_STOP;
    _delay_us(IR_PULSE_LEN*IR_PULSE_MARK);
  }
  //Send 0
  for(i=0;i<8;i++) {
    PWM_START;
    _delay_us(IR_PULSE_LEN);
    PWM_STOP;
    _delay_us(IR_PULSE_LEN*IR_PULSE_SPACE);
  }
}
