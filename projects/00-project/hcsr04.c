/*
 * ---------------------------------------------------------------------
 * Author:      Milan Hornik, Tomas Dubina
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-20
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Racing car, Track time and round measurements.
 * HC-SR04 ultrasonic sensor source file
 */

#include <util/delay.h>
#include "main.h"
#include "hcsr04.h"
#include "gpio.h"
#include "millis.h"
#include "uart.h"

void USendTrigger(uint8_t pin_numD) {
  _delay_us(2);
  GPIO_write(&PORTD,pin_numD,HIGH);
  _delay_us(10);  // 10 us delay
  GPIO_write(&PORTD,pin_numD,LOW);
  //_delay_us(1);
}

uint32_t UReadDistance(uint8_t select) {
  uint32_t DistanceTime=0;
  uint8_t ReadStatus=0;

  if(select == USENSOR_LEFT) {
    USendTrigger(USENSOR_TRIG_PIN);
    while(ReadStatus == 0) {
      while(GPIO_read(&PIND,USENSOR_ECHO_PIN)) {
        DistanceTime++;
        ReadStatus = 1;
      }
    }
  }
  else if (select == USENSOR_RIGHT) {
    USendTrigger(USENSOR_TRIG_PIN_2);
    while(ReadStatus == 0) {
      while(GPIO_read(&PIND,USENSOR_ECHO_PIN_2)) {
        DistanceTime++;
        ReadStatus = 1;
      }
    }
  }
  if(DistanceTime < 60) { // pokud vyjde mene nez 22 mm
    DistanceTime = 60;
  }
  return (DistanceTime * 0.04239582 - 0.311903)*10; // vzdalenost v mm, cisla urcena merenim
}
