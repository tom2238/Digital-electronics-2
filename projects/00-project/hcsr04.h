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
#define  HCSR04_CALIBRATE 70 // in mm 70
/**
 * @brief Vyšle echo impulz, senzor HC-SR04
 * @author Tomáš Dubina
 * @return nic
 * @param nic
 */
void USensorTrigger(uint8_t select);

/**
 * @author Tomáš Dubina
 * @brief Prevede pocet pulzů na délku v mm
 * @param pulses Počet pulzů
 * @return Vzdálenost od cíle v mm
 */
uint16_t UPulsesToMilimeters(uint16_t pulses);

#endif /*  HCSR04_H_INCLUDED  */
