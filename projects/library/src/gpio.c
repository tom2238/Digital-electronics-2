#include "gpio.h"

void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num) // DDRx
{
    // Body of the  function7
    *reg_name  |= _BV(pin_num);
}

void  GPIO_config_input_nopull(volatile  uint8_t *reg_name,volatile  uint8_t *port_name , uint8_t  pin_num) //DDRx
{
    *reg_name &= ~_BV(pin_num);
    *port_name &= ~_BV(pin_num);

}

void  GPIO_config_input_pullup(volatile  uint8_t *reg_name,volatile  uint8_t *port_name , uint8_t  pin_num) //DDRX
{
    *reg_name &= ~_BV(pin_num);
    *port_name  |= _BV(pin_num);
}
void  GPIO_write(volatile  uint8_t *reg_name , uint8_t  pin_num, uint8_t  pin_val) // PORTx
{    
    if (pin_val)
    {
        *reg_name  |= _BV(pin_num);
    }
    else
    {
        *reg_name &= ~_BV(pin_num);
    }
}
void  GPIO_toggle(volatile  uint8_t *reg_name , uint8_t  pin_num) // PORTx
{
    *reg_name ^= _BV(pin_num);
}
uint8_t  GPIO_read(volatile  uint8_t *reg_name , uint8_t  pin_num) // PINx
{
    return bit_is_set(*reg_name , pin_num);
}