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

void USensorTrigger(uint8_t select) {
  if(distance.complete && select==0) {
    distance.pulses = 0;
    USendTrigger(USENSOR_TRIG_PIN);
    distance.enable = TRUE;
    distance.complete = FALSE;
  }
  if(distance2.complete && select==1) {
    distance2.pulses = 0;
    USendTrigger(USENSOR_TRIG_PIN_2);
    distance2.enable = TRUE;
    distance2.complete = FALSE;
  }
  
}

uint16_t UPulsesToMilimeters(uint16_t pulses) {
  double PulsesTime = pulses * 16; // In us
  double SpeedOfSound = 0.03313 + 0.0000606 * 19.307; // In cm/s
  double uDistance = PulsesTime / 2.0 * SpeedOfSound; // In cm
  if(uDistance < 10) {
    uDistance = 10;
  }
  return (uint16_t)(uDistance*10-HCSR04_CALIBRATE_MM); // In mm
}

void USendTrigger(uint8_t pin_numD) {
  GPIO_write(&PORTD,pin_numD,LOW);
  _delay_us(1);
  GPIO_write(&PORTD,pin_numD,HIGH);
  _delay_us(10);  // 10 us delay
  GPIO_write(&PORTD,pin_numD,LOW);
  _delay_us(1);
}
