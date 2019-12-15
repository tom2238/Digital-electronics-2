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
 * @brief Struktura pro ulozeni casu ve formate SS:MS (minuty se nepouzivaji)
 * @param millis Cast pro ulozeni milisekund
 * @param seconds Cast pro ulozeni sekund
 * @param minutes Cast pro ulozeni minut
**/ 
typedef struct{
  unsigned int millis;
  unsigned int seconds;
  unsigned int minutes;
} Clock;
/**
 * @brief Struktura pro mereni casu auta
 * @param CurrentMillis Cas aktualniho kola
 * @param LastMillis Cas posledniho kola
 * @param BestMillis Nejlepsi cas kola
 * @param CurrentLap Aktualni pocet najetych kol
 * @param millis Pomocna promena casu
 * @param LastDebounceTime Pauza po projeti
 * @param Distance Namerena vzdalenost senzorem
 * @param CCurrent Aktualni cas kolo ve formatu SS:MS
 * @param CBest Nejlepsi cas kola ve formatu SS:MS
 **/
typedef struct{
  unsigned long CurrentMillis;
  unsigned long LastMillis;
  unsigned long BestMillis;
  unsigned int CurrentLap;
  unsigned long millis;
  unsigned long LastDebounceTime;
  uint16_t Distance;
  Clock CCurrent;
  Clock CBest;
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
#define USENSOR_LEFT         0 // Senzor vlevo, auto 1
#define USENSOR_RIGHT        1 // Senzor vpravo, auto 2
#define UART_DEBUG             // enable debug via uart
#define DEBOUNCE_DELAY       40// cas cekani v ms

/* Variables */
CarLap auto1,auto2;

/* Function prototypes */
/**
 * @author Milan Hornik, Tomas Dubina
 * @brief Vytiskne informace o aute na LCD
 * @param car Objekt auta ktery se zobrazi
 * @param offset Posun pozice na displeji v pixelech, plati pouze pro osu Y
 * @return Nic
 */
void PrintCars(CarLap car, uint8_t offset);
/**
 * @author Milan Horník
 * @brief Vypise cele cislo na UART
 * @param number Cislo ktere se ma zobrazit
 * @return Nic
 */
void uart_putint(long number);
/**
 * @author Milan Horník
 * @brief Vypise cele nezaporne cislo na UART
 * @param number Cislo ktere se ma zobrazit
 * @return Nic
 */
void uart_putuint(unsigned long number);
/**
 * @author Tomáš Dubina
 * @brief Smaze informace a casech a kolech auticka
 * @param car Auto ktere se ma vynulovat
 * @return Objekt auta s vynulovanymi hodnotami
 */
CarLap ClearCar(CarLap car);
/**
 * @author Tomas Dubina
 * @brief Prepocte milisekundy na sekundy a milisekundy
 * @param value Hodnota v milisekundach ktera se prevede
 * @return Objekt hodin s prevedenymi hodnotami
 */ 
Clock MillisToClock(unsigned long value);
/**
 * @author Tomas Dubina, Milan Hornik
 * @brief Vypocita cas kola, cas nejlepsiho kola a pocet ujetych kol
 * @param car Auto ke kteremu se pripocte cas a kola
 * @return Objekt auta s novymi casy
 */
CarLap CalculateCar(CarLap car);

#endif /*  MAIN_RACINGCAR_H_INCLUDED  */
