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
 * @author Tomáš Dubina, Milan Horník
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

/**
 * @brief Struktura pro čas auta
 * @param microseconds
 * @param seconds
 * @param minutes
 * @param totallap
 * @param enable
 **/
typedef struct{
  uint16_t microsecond;
  uint8_t seconds;
  uint8_t minutes;
  uint16_t totallap;
  uint8_t enable;
} CarLap;

/* Define */
// Ports
#define IR_LED_PIN           PB1  // D9  Výstupní pin vysílací IR diody
#define IR_SENSOR_PIN        PB2  // D10 Vstupní pin IR přijímače
#define USENSOR_ECHO_PIN     PD2  // D2  Vstupní echo pin
#define USENSOR_TRIG_PIN     PD3  // D3  Výstupní trigger pin
#define USENSOR_ECHO_PIN_2   PD4  // D4  Vstupní echo pin 2
#define USENSOR_TRIG_PIN_2   PD5  // D5  Výstupní trigger pin 2
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
#define IR_PULSE_LEN         250/2 // Délka impulzu v us
#define IR_PULSE_MARK        3  // Délka pauzy jedničky (xLEN)
#define IR_PULSE_SPACE       1  // Délka pauzy nuly (xLEN)
#define USENSOR_LEFT         0  // Senzor vlevo, auto 1
#define USENSOR_RIGHT        1  // Senzor vpravo, auto 2

/* Variables */
CountPulse distance,distance2;
CarLap auto1;

/* Function prototypes */
/**
 * @author Tomáš Dubina
 * @brief Nastaví frekvenci a střídu PWM
 * @param frequency frekvence PWM v Hz
 * @param percentage střída v %
 * @return Nic
 */
void FrequencyPWM(uint16_t frequency, uint8_t percentage);
/**
 * @author Tomáš Dubina
 * @brief Trvale posílá sekvenci 8 nul a 8 jedniček
 * @param Nic
 * @return Nic
 */
void SendIR();
/**
 * @author
 * @brief Vytiskne informace o aute na LCD
 * @param car objekt auta
 * @param offset Posun pozice na displeji v pixelech, plati pouze pro osu Y
 * @return nic
 */
void PrintCars(CountPulse car, uint8_t offset);
/**
 *
 */
CarLap AddCarTime(CarLap carlap);

CarLap ClearCarTime(CarLap carlap);
// https://www.gadgetronicx.com/lap-timer-slot-car-laser-arduino/
#endif /*  MAIN_RACINGCAR_H_INCLUDED  */
