/*
 * ---------------------------------------------------------------------
 * Author:      Milan Hornik, Tomas Dubina
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-20
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Racing car, Track time and round measurements.
 * Main header file
 */

#ifndef  MAIN_RACINGCAR_H_INCLUDED
#define  MAIN_RACINGCAR_H_INCLUDED

/* Typedef */
/**
 * @author Tomáš Dubina
 * @brief Struktura pro čítač impulzů
 * @param pulses Počet načítaných impulzů
 * @param enable Povolit počítání impulzů
 * @param complete Počítání impulzů dokončeno
 */
typedef struct{
  unsigned int pulses;
  uint8_t enable;
  uint8_t complete;
} CountPulse;

/* Define */
// Ports
#define IR_LED_PIN           PB1  // Výstupní pin vysílací IR diody
#define IR_SENSOR_PIN        PB2  // Vstupní pin IR přijímače
#define USENSOR_ECHO_PIN     PD2  // Vstupní echo pin
#define USENSOR_TRIG_PIN     PD3  // Výstupní trigger pin
#define USENSOR_ECHO_PIN_2   PD4  // Vstupní echo pin 2
// Uart
#define UART_BAUD_RATE       9600
// Uart colors
#define ANSI_UART_C_NORMAL   uart_puts("\033[0m")
#define ANSI_UART_C_YELLOW   uart_puts("\e[33m")
#define ANSI_UART_C_RED      uart_puts("\e[31m")
#define ANSI_UART_C_GREEN    uart_puts("\e[92m")
#define ANSI_UART_C_BLUE     uart_puts("\e[34m")
#define ANSI_UART_C_CYAN     uart_puts("\e[96m")
#define ANSI_UART_C_MAGENTA  uart_puts("\e[35m")
#define ANSI_UART_C_BLINK    uart_puts("\e[5m")
// Values
#define HIGH                 1 // Vysoká
#define LOW                  0 // Nízká
#define TRUE                 1 // Pravda
#define FALSE                0 // Nepravda
#define PWM_DIVIDER          1 // Delička PWM časovače
#define PWM_FREQUENCY        38000 // Nosný kmitočet IR záření
#define PWM_STOP             FrequencyPWM(PWM_FREQUENCY, 0)  // Nevýsílá
#define PWM_START            FrequencyPWM(PWM_FREQUENCY, 50) // Vysílá nosnou, střída 50%
#define IR_PULSE_LEN         500/2 // Délka impulzu v us
#define IR_PULSE_MARK        3  // Délka pauzy jedničky (xLEN)
#define IR_PULSE_SPACE       1  // Délka pauzy nuly (xLEN)

/* Variables */
CountPulse distance,distance2;
CountPulse irdetect; 

#endif /*  MAIN_RACINGCAR_H_INCLUDED  */
