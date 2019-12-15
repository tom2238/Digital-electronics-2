#ifndef INITALL_H
#define INITALL_H

/**
 * @author Milan Hornik
 * @brief Inicializace vstupnich a vystupnich pinu
 * @param Nic
 * @return Nic
 */
void GPIOInit();
/**
 * @author Milan Hornik
 * @brief Inicializace UART rozhrani
 * @param Nic
 * @return Nic
 */
void UARTInit();
/**
 * @author Tomas Dubina
 * @brief Inicializace čítače/časovače 0
 * @param Nic
 * @return Nic
 */
void TimerInit();
/**
 * @author Milan Hornik
 * @brief Inicializace Nokia LCD displeje
 * @param Nic
 * @return Nic
 */
void NokiaLCDInit();
/**
 * @author Milan Hornik
 * @brief Inicializace objektu na vychozi hodnoty
 * @param Nic
 * @return Nic
 */
void ObjectsInit();

#endif // INITALL_H
