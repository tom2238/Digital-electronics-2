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

/* Includes */
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

/**
 * @brief Posledni stav senzoru
 */
uint8_t LSensorStateLast = LOW;
/**
 * @brief Aktualni prectena hodnota senzoru
 */
uint8_t LSensorStateRead = LOW;
/**
 * @brief Aktualni ulozena hodnota senzoru
 */
uint8_t LSensorStateCurrent = LOW;
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
      //auto2.LastDebounceTime = millis();
    } 
    /*
    if ((millis() - auto1.LastDebounceTime) > DEBOUNCE_DELAY) {
       if (LSensorStateRead != LSensorStateCurrent) {
         LSensorStateCurrent = LSensorStateRead;
         auto1.Distance = UReadDistance(USENSOR_LEFT);
         // _delay_ms(1);
         // auto2.Distance = UReadDistance(USENSOR_RIGHT);

         if (LSensorStateCurrent == LOW) {
           //_delay_ms(1);
           
           if(auto1.Distance < 100) {
             auto1 = CalculateCar(auto1);
           }
           //if(auto2.Distance < 120) {
           //  auto2 = CalculateCar(auto2);
           //}
         }
       }
    }*/
    if ((millis() - auto1.LastDebounceTime) > DEBOUNCE_DELAY) {
       if (LSensorStateRead != LSensorStateCurrent) {
         LSensorStateCurrent = LSensorStateRead;
         int i;
              
         if (LSensorStateCurrent == LOW) {
           //_delay_ms(1);
           for(i=0;i<2;i++) {
           auto1.Distance += UReadDistance(USENSOR_LEFT);
           //_delay_us(5);
           }
           for(i=0;i<2;i++) {
           auto2.Distance += UReadDistance(USENSOR_RIGHT);
           //_delay_us(5);
           }
           auto1.Distance = auto1.Distance / 2;
           auto2.Distance = auto2.Distance / 2;
           if(auto1.Distance < 100 && auto1.Distance > 30) {
             auto1 = CalculateCar(auto1);
           }
           if(auto2.Distance < 100 && auto2.Distance > 30) {
             auto2 = CalculateCar(auto2);
           }
         }
       }
    }
    // Ulozit aktualni stav
    LSensorStateLast = LSensorStateRead;
    auto1.millis = millis();
    auto2.millis = millis();

    // neni prvni kolo
    if (auto1.CurrentLap > 0) {
      PrintCars(auto1, 24);
      /*uart_puts("A1 Cas ");
      uart_putuint(auto1.millis - auto1.CurrentMillis);
      uart_puts(" ms || Nej ");
      uart_putuint(auto1.BestMillis);
      uart_puts(" ms || Kola ");
      uart_putuint(auto1.CurrentLap);
      uart_puts(" || Vzd ");
      uart_putuint(auto1.Distance);
      uart_puts("mm ||");*/
    } else {
      nokia_lcd_set_cursor(0,0);
      nokia_lcd_write_string("Cekam ...     ",1);
      nokia_lcd_render();
    }
    if (auto2.CurrentLap > 0) {
      PrintCars(auto2, 0);
      /*uart_puts("A2 Cas ");
      uart_putuint(auto2.millis - auto2.CurrentMillis);
      uart_puts(" ms || Nej ");
      uart_putuint(auto2.BestMillis);
      uart_puts(" ms || Kola ");
      uart_putuint(auto2.CurrentLap);
      uart_puts(" || Vzd ");
      uart_putuint(auto2.Distance);
      uart_puts("mm \n");*/
    } else {
      nokia_lcd_set_cursor(0,24);
      nokia_lcd_write_string("Cekam ...     ",1);
      nokia_lcd_render();
    }

    //_delay_ms(100);

  }
  return 0;
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
  car.CCurrent = MillisToClock(car.millis - car.CurrentMillis);
  car.CBest = MillisToClock(car.BestMillis);
  nokia_lcd_set_cursor(0,0+offset);
  char numstring[20];
  nokia_lcd_write_string("Cas ",1);
  ltoa(car.CCurrent.seconds, numstring , 10);
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(",",1);
  ltoa(car.CCurrent.millis/10, numstring , 10);
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(" s     ",1);
  nokia_lcd_set_cursor(0,8+offset);
  ltoa(car.CBest.seconds, numstring , 10);
  nokia_lcd_write_string("Nej ",1);
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(",",1);
  ltoa(car.CBest.millis/10, numstring , 10);
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(" s     ",1);
  nokia_lcd_set_cursor(0,16+offset);
  ltoa(car.CurrentLap, numstring , 10); 
  nokia_lcd_write_string("Kola ",1);
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(" D",1);
  ltoa(car.Distance, numstring , 10); 
  nokia_lcd_write_string(numstring,1);
  nokia_lcd_write_string(" ",1);
  nokia_lcd_render();
}

void uart_putint(long number) {
  char numstring[20];
  ltoa(number, numstring , 10);
  uart_puts(numstring);
}

void uart_putuint(unsigned long number) {
  char numstring[20];
  ultoa(number, numstring , 10);
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
  CarRet.Distance = 0;
  return CarRet;
}

Clock MillisToClock(unsigned long value) {
  Clock result;
  result.seconds = (unsigned int)(value/1000);
  result.millis = value - result.seconds * 1000;
  return result;
}

CarLap CalculateCar(CarLap car) {
  CarLap result = car;
  result.millis = millis();
  if (result.CurrentLap > 0) {
    result.LastMillis = result.millis - result.CurrentMillis; // uloz aktualni kolo
    if (result.LastMillis < result.BestMillis || result.BestMillis == 0) {
      result.BestMillis = result.LastMillis; // ulozit nejlepsi
    }
  } 
  result.CurrentMillis = result.millis; // reset aktualnich
  result.CurrentLap++;
  return result;
}