#ifndef APC1_STM32_IO_UART_H_
#define APC1_STM32_IO_UART_H_

#include "stm32f4xx_hal.h"

typedef struct {
    UART_HandleTypeDef *huart;
} apc1_uart_interface_t;

HAL_StatusTypeDef apc1_uart_interface_init(apc1_uart_interface_t *iface, UART_HandleTypeDef *huart);
HAL_StatusTypeDef apc1_uart_interface_read(apc1_uart_interface_t *iface, float *co2, float *temp, float *hum);

#endif
