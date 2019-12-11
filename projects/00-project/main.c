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

volatile uint8_t EchoPinOld  = 0xFF;
uint8_t LSensorStateLast = LOW;
uint8_t LSensorStateRead = LOW;
uint8_t LSensorStateCurrent = LOW;

/* Functions */

/**
 * @author Milan Horník, Tomáš Dubina
 * @brief Hlavní program
 * @param  Nic
 * @return Návratový kod
 */
int main(void) { 
  UARTInit();
  GPIOInit();
  NokiaLCDInit();
  ObjectsInit();
  TimerInit();
  PWMInit();
  _delay_ms(200);
  uart_puts("Autodraha pripravena\n");
  _delay_ms(200);
  /* Infinite loop */
  for (;;) {
    LSensorStateRead = GPIO_read(&PINB,IR_SENSOR_PIN);
    if (LSensorStateRead != LSensorStateLast) {
      auto1.LastDebounceTime = millis();
    } 

    if ((millis() - auto1.LastDebounceTime) > DEBOUNCE_DELAY) {
       if (LSensorStateRead != LSensorStateCurrent) {
         LSensorStateCurrent = LSensorStateRead;

         if (LSensorStateCurrent == LOW) {
           auto1.millis = millis();
           if (auto1.CurrentLap > 0) {
             auto1.LastMillis = auto1.millis - auto1.CurrentMillis; // uloz aktualni kolo
             if (auto1.LastMillis < auto1.BestMillis || auto1.BestMillis == 0) {
               auto1.BestMillis = auto1.LastMillis; // ulozit nejlepsi
             }
           } 
           auto1.CurrentMillis = auto1.millis; // reset aktualnich
           auto1.CurrentLap++;
         }
       }
    }
    // Ulozit aktualni stav
    LSensorStateLast = LSensorStateRead;
    auto1.millis = millis();

    // neni prvni kolo
    if (auto1.CurrentLap > 0) {
      uart_putint(auto1.millis - auto1.CurrentMillis);
      uart_puts("\n");
    } else {
      uart_putint(auto1.millis - auto1.CurrentMillis);
      uart_puts("\n");
    }

    /*if(GPIO_read(&PINB,IR_SENSOR_PIN)) {
      ANSI_UART_C_RED; // Prochazi
      uart_puts("X");
      ANSI_UART_C_NORMAL;
    }
    else {
      ANSI_UART_C_GREEN; // Prerusen
      uart_puts("X");
      ANSI_UART_C_NORMAL;
    }*/

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
   */
    /*USensorTrigger(USENSOR_LEFT);
    _delay_ms(50);
    USensorTrigger(USENSOR_RIGHT);
    */
    //_delay_ms(100);

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

void PrintCars(CarLap car, uint8_t offset) {
  char dist[8];
  uint16_t cm = UReadDistance(USENSOR_LEFT);
  car.CurrentLap = car.CurrentLap;
  nokia_lcd_set_cursor(0,0+offset);
  nokia_lcd_write_string(dist,1);
  nokia_lcd_write_string(" cm       ",1);    
  if ((cm>2)&&(cm<8)) {
    nokia_lcd_set_cursor(0,8+offset);
    nokia_lcd_write_string(">Obsazeno  ",1);
  }
  else {
    nokia_lcd_set_cursor(0,8+offset);
    nokia_lcd_write_string(">Volno     ",1);
  }
  nokia_lcd_render();
}

void uart_putint(int number) {
  char numstring[8];
  itoa(number, numstring , 10);
  uart_puts(numstring);
}

CarLap ClearCar(CarLap car) {
  CarLap CarRet = car;
  CarRet.CurrentMillis = 0;
  CarRet.LastMillis = 0;
  CarRet.BestMillis = 0;
  CarRet.CurrentLap = 0;
  CarRet.millis = 0;
  CarRet.LastDebounceTime = 0;
  return CarRet;
}