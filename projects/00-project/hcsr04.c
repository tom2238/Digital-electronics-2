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

void USensorTrigger() {
  distance.complete = FALSE;
  distance.pulses = 0;
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,LOW);
  _delay_us(100);
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,HIGH);
  _delay_us(10);  // 10 us delay
  GPIO_write(&PORTB,USENSOR_TRIG_PIN,LOW);
  distance.enable = TRUE;
}

uint16_t UPulsesToMilimeters(uint16_t pulses) {
  double PulsesTime = pulses * 16; // In us
  double SpeedOfSound = 0.03313 + 0.0000606 * 19.307; // In cm/s
  double uDistance = PulsesTime / 2.0 * SpeedOfSound; // In cm
  return (uint16_t)(uDistance*10); // In mm
}
