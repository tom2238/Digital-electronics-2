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

/**
 * @author Milan Horník
 * @brief Vyšle trigger pulz
 * @param pin_numD Pin na který se pulz pošle
 * @return nic
 */
void USendTrigger(uint8_t pin_numD);
/**
 * @author Milan Hornik, Tomas Dubina
 * @brief Vrati vzdalenost od objektu
 * @param select Cislo senzoru kde se bude cist
 * @return Zmerena vzdalenost v milimetrech
 */
uint32_t UReadDistance(uint8_t select);

#endif /*  HCSR04_H_INCLUDED  */
