#ifndef APC1_STM32_H_
#define APC1_STM32_H_

#include "apc1_stm32_io_uart.h"   // or apc1_stm32_io_i2c.h
#include "apc1_stm32_defines.h"

typedef struct {
    apc1_uart_t uart;
} apc1_stm32_t;

HAL_StatusTypeDef apc1_stm32_init_uart(apc1_stm32_t *apc1, UART_HandleTypeDef *huart);
HAL_StatusTypeDef apc1_stm32_read(apc1_stm32_t *apc1, uint8_t *response);

#endif
