/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
uint8_t  value = 0;
/*  Global  variables  -------------------------------------------------------*/
uint8_t user_symbol_size = 8*3;
uint8_t lcd_user_symbols[] = {0x00, 0x0A, 0x0E, 0x0E, 0x15, 0x04, 0x0A, 0x11, 0x04, 0x0e, 0x1f, 0x15, 0x1f, 0x0a, 0x11, 0x0a, 0x04, 0x0e, 0x1f, 0x15, 0x1f, 0x0a, 0x15, 0x1b};
uint8_t progressbar_val = 0;
int ipris = 12;
int main(void)
{
    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor */
    lcd_init(LCD_DISP_ON);

    // Display string without auto linefeed
    lcd_puts("Counter");
    /*lcd_gotoxy(0,1);
    lcd_putc('$');
    lcd_gotoxy(6,1);
    lcd_puts("0b");*/
    // TODO: Display variable value in decimal, binary, and hexadecimal
    // Set  pointer  to  beginning  of CG RAM  me
    lcd_command(1<<LCD_CGRAM);
    int i = 0;
    for(i=0;i<user_symbol_size;i++) {
      lcd_data(lcd_user_symbols[i]);
    }
    
    //lcd_gotoxy(13,0);
    //lcd_putc (0x00);
    //lcd_putc (0x01);
    //lcd_putc (0x02);
    
    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    /* TODO: Design at least two user characters and store them in 
     *       the display memory */

    // Enables interrupts by setting the global interrupt mask
    sei();
    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Increment counter value form 0 to 255
    char  lcd_string [8];
    itoa(value , lcd_string , 10);
    lcd_gotoxy(9,0);
    lcd_puts(lcd_string);
    
    /*lcd_gotoxy(1,1);
    
    itoa(value , lcd_string , 16);
    lcd_puts(lcd_string);

    lcd_gotoxy(8,1);
    itoa(value , lcd_string , 2);
    lcd_puts(lcd_string);*/

    if(value != 255) {
      value++;
    }
    else {
      lcd_gotoxy(9,0);
      lcd_puts("   ");
      /*lcd_gotoxy(1,1);
      lcd_puts("  ");
      lcd_gotoxy(8,1);
      lcd_puts("        ");*/
      value=0;
      progressbar_val=0;
      lcd_gotoxy(0,1);
      lcd_puts("                ");
    }
    
    ipris++;
    if(ipris>=16)
    ipris=12;
    
    lcd_gotoxy(ipris,0);
    if(value % 2) {
       
      lcd_putc(0x01);
    }
    else {
      lcd_putc(0x02); 
    }
    if((value % 16)==0) {
      lcd_gotoxy(progressbar_val,1);
      lcd_putc(0xFF);
      progressbar_val++;
    }

}


