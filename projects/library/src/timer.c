/* Includes ----------------------------------------------------------*/
#include "timer.h"

/* Define ------------------------------------------------------------*/

/* Functions ---------------------------------------------------------*/
void TIM_config_prescaler(uint8_t timer_name,
                          uint8_t presc_val)
{
    /* Timer/Counter0 */
    if (timer_name == TIM0) {
        switch (presc_val) {
            case TIM_PRESC_1:
                /* 001 */
                TCCR0B = TCCR0B & ~_BV(CS02);
                TCCR0B = TCCR0B & ~_BV(CS01);
                TCCR0B = TCCR0B |  _BV(CS00);
                break;
            case TIM_PRESC_8:
                /* 010 */
                TCCR0B = TCCR0B & ~_BV(CS02);
                TCCR0B = TCCR0B |  _BV(CS01);
                TCCR0B = TCCR0B & ~_BV(CS00);
                break;
            case TIM_PRESC_64:
                /* 011 */
                TCCR0B = TCCR0B & ~_BV(CS02);
                TCCR0B = TCCR0B |  _BV(CS01);
                TCCR0B = TCCR0B |  _BV(CS00);
                break;
            case TIM_PRESC_256:
                /* 100 */
                TCCR0B = TCCR0B |  _BV(CS02);
                TCCR0B = TCCR0B & ~_BV(CS01);
                TCCR0B = TCCR0B & ~_BV(CS00);
                break;
            case TIM_PRESC_1024:
                /* 101 */
                TCCR0B = TCCR0B |  _BV(CS02);
                TCCR0B = TCCR0B & ~_BV(CS01);
                TCCR0B = TCCR0B |  _BV(CS00);
                break;
            default:
                /* 000: No clock source (Timer/Counter stopped) */
                TCCR0B = TCCR0B & ~_BV(CS02);
                TCCR0B = TCCR0B & ~_BV(CS01);
                TCCR0B = TCCR0B & ~_BV(CS00);
        }
    }
    /* Timer/Counter1 */
    else if (timer_name == TIM1) {
        // TODO: Set prescaler values for Timer/Counter1
        switch (presc_val) {
            case TIM_PRESC_1:
                /* 001 */
                TCCR1B = TCCR1B & ~_BV(CS12);
                TCCR1B = TCCR1B & ~_BV(CS11);
                TCCR1B = TCCR1B |  _BV(CS10);
                break;
            case TIM_PRESC_8:
                /* 010 */
                TCCR1B = TCCR1B & ~_BV(CS12);
                TCCR1B = TCCR1B |  _BV(CS11);
                TCCR1B = TCCR1B & ~_BV(CS10);
                break;
            case TIM_PRESC_64:
                /* 011 */
                TCCR1B = TCCR1B & ~_BV(CS12);
                TCCR1B = TCCR1B |  _BV(CS11);
                TCCR1B = TCCR1B |  _BV(CS10);
                break;
            case TIM_PRESC_256:
                /* 100 */
                TCCR1B = TCCR1B |  _BV(CS12);
                TCCR1B = TCCR1B & ~_BV(CS11);
                TCCR1B = TCCR1B & ~_BV(CS10);
                break;
            case TIM_PRESC_1024:
                /* 101 */
                TCCR1B = TCCR1B |  _BV(CS12);
                TCCR1B = TCCR1B & ~_BV(CS11);
                TCCR1B = TCCR1B |  _BV(CS10);
                break;
            default:
                /* 000: No clock source (Timer/Counter stopped) */
                TCCR1B = TCCR1B & ~_BV(CS12);
                TCCR1B = TCCR1B & ~_BV(CS11);
                TCCR1B = TCCR1B & ~_BV(CS10);
        }
    }
    /* Timer/Counter2 */
    else {
        // TODO: Set prescaler values for Timer/Counter2
        switch (presc_val) {
            case TIM_PRESC_1:
                /* 001 */
                TCCR2B = TCCR2B & ~_BV(CS22);
                TCCR2B = TCCR2B & ~_BV(CS21);
                TCCR2B = TCCR2B |  _BV(CS20);
                break;
            case TIM_PRESC_8:
                /* 010 */
                TCCR2B = TCCR2B & ~_BV(CS22);
                TCCR2B = TCCR2B |  _BV(CS21);
                TCCR2B = TCCR2B & ~_BV(CS20);
                break;  
            case TIM_PRESC_32:
                /* 011 */
                TCCR2B = TCCR2B & ~_BV(CS22);
                TCCR2B = TCCR2B |  _BV(CS21);
                TCCR2B = TCCR2B |  _BV(CS20);
                break;
            case TIM_PRESC_64:
                /* 100 */
                TCCR2B = TCCR2B & ~_BV(CS22);
                TCCR2B = TCCR2B |  _BV(CS21);
                TCCR2B = TCCR2B |  _BV(CS20);
                break; 
            case TIM_PRESC_128:
                /* 101 */
                TCCR2B = TCCR2B |  _BV(CS22);
                TCCR2B = TCCR2B & ~_BV(CS21);
                TCCR2B = TCCR2B |  _BV(CS20);
                break;     
            case TIM_PRESC_256:
                /* 110 */
                TCCR2B = TCCR2B |  _BV(CS22);
                TCCR2B = TCCR2B |  _BV(CS21);
                TCCR2B = TCCR2B & ~_BV(CS20);
                break;
            case TIM_PRESC_1024:
                /* 111 */
                TCCR2B = TCCR2B |  _BV(CS22);
                TCCR2B = TCCR2B |  _BV(CS21);
                TCCR2B = TCCR2B |  _BV(CS20);
                break;
            default:
                /* 000: No clock source (Timer/Counter stopped) */
                TCCR2B = TCCR2B & ~_BV(CS22);
                TCCR2B = TCCR2B & ~_BV(CS21);
                TCCR2B = TCCR2B & ~_BV(CS20);
        }
    }
}

/*--------------------------------------------------------------------*/
void TIM_config_interrupt(uint8_t timer_name,
                          uint8_t interr_mode)
{
    /* Timer/Counter0 */
    if (timer_name == TIM0) {
        switch (interr_mode) {
            case TIM_OVERFLOW_ENABLE:
                TIMSK0 = TIMSK0 | _BV(TOIE0);
                break;
            case TIM_OVERFLOW_DISABLE:
                TIMSK0 = TIMSK0 & ~_BV(TOIE0);
                break;
            default:
                /* Disable overflow interrupt */
                TIMSK0 = TIMSK0 & ~_BV(TOIE0);
        }
    }
    /* Timer/Counter1 */
    else if (timer_name == TIM1) {
        // TODO: Enable/disable interupt for Timer/Counter1
        switch (interr_mode) {
            case TIM_OVERFLOW_ENABLE:
                TIMSK1 = TIMSK1 | _BV(TOIE1);
                break;
            case TIM_OVERFLOW_DISABLE:
                TIMSK1 = TIMSK1 & ~_BV(TOIE1);
                break;
            default:
                /* Disable overflow interrupt */
                TIMSK1 = TIMSK1 & ~_BV(TOIE1);
        }
    }
    /* Timer/Counter2 */
    else {
        // TODO: Enable/disable interupt for Timer/Counter2
        switch (interr_mode) {
            case TIM_OVERFLOW_ENABLE:
                TIMSK2 = TIMSK2 | _BV(TOIE2);
                break;
            case TIM_OVERFLOW_DISABLE:
                TIMSK2 = TIMSK2 & ~_BV(TOIE2);
                break;
            default:
                /* Disable overflow interrupt */
                TIMSK2 = TIMSK2 & ~_BV(TOIE2);
        }
    }
}