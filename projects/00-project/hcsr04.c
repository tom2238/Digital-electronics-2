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
  uint32_t disTime=0;

  uint8_t readStatus=0;

  if(select == USENSOR_LEFT) {
    USendTrigger(USENSOR_TRIG_PIN);
    while(readStatus == 0) {
      while(GPIO_read(&PIND,USENSOR_ECHO_PIN)) {
        disTime++;
        readStatus = 1;
      }
    }
  }
  else if (select == USENSOR_RIGHT) {
    USendTrigger(USENSOR_TRIG_PIN_2);
    while(readStatus == 0) {
      while(GPIO_read(&PIND,USENSOR_ECHO_PIN_2)) {
        disTime++;
        readStatus = 1;
      }
    }
  }
  /*if(select == USENSOR_LEFT) {
    USendTrigger(USENSOR_TRIG_PIN);
    disTime = pulseIn(USENSOR_ECHO_PIN,HIGH);
  }
  else if (select == USENSOR_RIGHT) {
    USendTrigger(USENSOR_TRIG_PIN_2);
    disTime = pulseIn(USENSOR_ECHO_PIN_2,HIGH);
  }*/
  if(disTime < 60) {
    disTime = 60;
  }
  return (disTime * 0.04239582 - 0.311903)*10;// *  0.00862;	//return data in mm
}
/*
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
    // cache the port and bit of the pin in order to speed up the
    // pulse width measuring loop and achieve finer resolution.  calling
    // digitalRead() instead yields much coarser resolution.
    unsigned long width = 0; // keep initialization out of time critical area

    // convert the timeout from microseconds to a number of times through
    // the initial loop; it takes 16 clock cycles per iteration.
    unsigned long numloops = 0;
    unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;

    // wait for any previous pulse to end
    while (GPIO_read(&PIND,pin) == state) {
        if (numloops++ == maxloops) {
            return 0;
        }
    }

    // wait for the pulse to start
    while (GPIO_read(&PIND,pin) != state) {
        if (numloops++ == maxloops) {
            return 0;
        }
    }

    // wait for the pulse to stop
    while (GPIO_read(&PIND,pin) == state) {
        if (numloops++ == maxloops) {
            return 0;
        }
        width++;
    }

    // convert the reading to microseconds. The loop has been determined
    // to be 20 clock cycles long and have about 16 clocks between the edge
    // and the start of the loop. There will be some error introduced by
    // the interrupt handlers.
    return clockCyclesToMicroseconds(width * 21 + 16);
}*/
/*
unsigned long pulseIn(uint8_t pin, uint8_t state) {
    if(pin) {}
    unsigned long pulseWidth = 0;
    unsigned long loopCount = 0;
    unsigned long loopMax = 5000000;

    // While the pin is *not* in the target state we make sure the timeout hasn't been reached.
    while (GPIO_read(&PIND,USENSOR_ECHO_PIN) != state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
    }

    // When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
    while (GPIO_read(&PIND,USENSOR_ECHO_PIN) == state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
        pulseWidth++;
    }

    // Return the pulse time in microsecond!
    return pulseWidth * 2.36; // Calculated the pulseWidth++ loop to be about 2.36uS in length.
}*/
