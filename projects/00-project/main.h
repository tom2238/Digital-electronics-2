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

/* Define */
// Ports
#define IR_LED_PIN           PB1
#define IR_SENSOR_PIN        PB2
#define USENSOR_ECHO_PIN     PB3
#define USENSOR_TRIG_PIN     PB4
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
#define HIGH                 1
#define LOW                  0
#define PWM_DIVIDER          1
#define PWM_FREQUENCY        38000
#define PWM_STOP             FrequencyPWM(50, 50)
#define PWM_START            FrequencyPWM(PWM_FREQUENCY, 50)

#endif /*  MAIN_RACINGCAR_H_INCLUDED  */
