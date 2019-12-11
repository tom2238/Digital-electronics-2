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
#include "initall.h"
#include "millis.h"

#define UART_DEBUG            // enable debug via uart
#define TIMER_COUNT_STEP 4096 // in us

volatile uint8_t EchoPinOld  = 0xFF;
unsigned long currentRunStartMillis = 0;
unsigned long lastMillis = 0;

/* Functions */

/**
 * @author Milan Horník, Tomáš Dubina
 * @brief Hlavní program
 * @param  Nic
 * @return Návratový kod
 */
int main(void) {
  GPIOInit();
  #ifdef UART_DEBUG
    UARTInit();
  #endif
  NokiaLCDInit();
  ObjectsInit();
  TimerInit();
  PWMInit();
  _delay_ms(500);
  //uart_puts("Autodraha pripravena\n");

  /* Infinite loop */
  for (;;) {
    if(GPIO_read(&PINB,IR_SENSOR_PIN)) {
      ANSI_UART_C_RED; // Prochazi
      uart_puts("X");
      ANSI_UART_C_NORMAL;
    }
    else {
      ANSI_UART_C_GREEN; // Prerusen
      uart_puts("X");
      ANSI_UART_C_NORMAL;
    }
    currentRunStartMillis = millis();
    //SendIR();

    /*if(GPIO_read(&PINB,IR_SENSOR_PIN) && cartimer == 0) {
      auto1.enable = TRUE;
      char time[8];
      itoa(auto1.seconds, time , 10);
      uart_puts(time);
      uart_puts(":");
      itoa(auto1.microsecond, time, 10);
      uart_puts(time);
      uart_puts(" s\n");
    }
    else {
      auto1 = ClearCarTime(auto1);
      auto1.enable = FALSE;
    }*/
    /*USensorTrigger(USENSOR_LEFT);
    _delay_ms(50);
    USensorTrigger(USENSOR_RIGHT);
    */
    _delay_ms(100);
    lastMillis = millis() - currentRunStartMillis;
    char time[8];
    itoa(lastMillis, time , 10);
    uart_puts(time);
    //uart_puts(" ms \n");

  }
  return 0;
}

/**
 * @author Tomáš Dubina
 * @brief Přerušení pokud dojde ke změně hodnoty na echo pinu PD2
 * @param Nic
 * @return Nic
 */
ISR(PCINT2_vect) {
  uint8_t EchoChanged;
  EchoChanged = PIND ^ EchoPinOld;
  EchoPinOld = PIND;
  if(distance.enable) {  
    if(EchoChanged & (1 << USENSOR_ECHO_PIN))  {
      #ifdef UART_DEBUG
      uart_puts("Zmena1|");
      #endif
      if(distance.pulses > 30) {
         distance.enable = FALSE;
         /*if(distance.pulses > 700) {
            distance.pulses = 700;
         }*/
         PrintCars(distance, 0);
         distance.complete = TRUE;
      }
    }
  }
  if(distance2.enable) {
    if(EchoChanged & (1 << USENSOR_ECHO_PIN_2))  {
      #ifdef UART_DEBUG
      uart_puts("Zmena2|");
      #endif
      if(distance2.pulses > 30) {
         distance2.enable = FALSE;
         /*if(distance2.pulses > 700) {
            distance2.pulses = 700;
         }*/
         PrintCars(distance2, 24);
         distance2.complete = TRUE;
      }    
    } 
  }
}

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

void PrintCars(CountPulse car, uint8_t offset) {
  char dist[8];
  uint16_t milimeters = UPulsesToMilimeters(car.pulses);
  itoa(milimeters, dist , 10);
  #ifdef UART_DEBUG
    uart_puts(dist);
    uart_puts(" mm \n");
  #endif
  nokia_lcd_set_cursor(0,0+offset);
  nokia_lcd_write_string(dist,1);
  nokia_lcd_write_string(" mm       ",1);    
  if ((milimeters>20)&&(milimeters<75)) {
    nokia_lcd_set_cursor(0,8+offset);
    nokia_lcd_write_string(">Obsazeno  ",1);
  }
  else {
    nokia_lcd_set_cursor(0,8+offset);
    nokia_lcd_write_string(">Volno     ",1);
  }
  nokia_lcd_render();
}

CarLap AddCarTime(CarLap carlap) {
  CarLap car = carlap;
  uint16_t secs = 0;
  car.microsecond += TIMER_COUNT_STEP;
  if(car.microsecond > 1000) {
    secs = car.microsecond / 1000;
    car.seconds += secs;
    car.microsecond = car.microsecond - secs*1000;
  }
  return car;
}

CarLap ClearCarTime(CarLap carlap) {
  CarLap car = carlap;
  car.microsecond = 0;
  car.seconds = 0;
  car.minutes = 0;
  return car;
}
