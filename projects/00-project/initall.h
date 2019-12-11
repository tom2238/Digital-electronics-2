#ifndef INITALL_H
#define INITALL_H

/**
 * @author Milan Horník
 * @brief Inicializace vstupních a výstupních pinů
 * @param Nic
 * @return Nic
 */
void GPIOInit();
/**
 * @author Milan Horník
 * @brief Inicializace UART rozhraní
 * @param Nic
 * @return Nic
 */
void UARTInit();
/**
 * @author Tomáš Dubina
 * @brief Inicializace čítače/časovače 0
 * @param Nic
 * @return Nic
 */
void TimerInit();
/**
 * @author
 * @brief NokiaLCDInit
 * @param nic
 * @return nic
 */
void NokiaLCDInit();
/**
 * @author Tomáš Dubina
 * @brief Inicializace PWM na čítači/časovači 1
 * @param Nic
 * @return Nic
 */
void PWMInit();
/**
 * @brief Inicializace objektu
 */
void ObjectsInit();

#endif // INITALL_H
