/*
 * ---------------------------------------------------------------------
 * Author:      Milan Hornik, Tomas Dubina
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-20
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Racing car, Track time and round measurements.
 * HC-SR04 ultrasonic sensor header file
 */

#ifndef  HCSR04_H_INCLUDED
#define  HCSR04_H_INCLUDED
#define  HCSR04_CALIBRATE_MM 70 // in: 70 mm ~ 200 us ~ 13 pulses
/**
 * @brief Vyšle trigger pulz a vybere sensor, senzor HC-SR04
 * @author Tomáš Dubina
 * @param Vyber senzoru (0 nebo 1)
 * @return nic
 */
void USensorTrigger(uint8_t select);
/**
 * @author Milan Horník
 * @brief Vyšle trigger pulz
 * @param Pin na který se pulz pošle
 * @return nic
 */
void USendTrigger(uint8_t pin_numD);


void usound_init(void);				//Paste in Main function

uint32_t UReadDistance(uint8_t select);			//Return the distance in centimeters
										//Recommended use this function with 20Hz frequency 


#endif /*  HCSR04_H_INCLUDED  */
