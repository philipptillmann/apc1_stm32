#include "apc1_stm32.h"

HAL_StatusTypeDef apc1_stm32_init_uart(apc1_stm32_t *apc1, UART_HandleTypeDef *huart) {
    return apc1_uart_init(&apc1->uart, huart);
}

HAL_StatusTypeDef apc1_stm32_read(apc1_stm32_t *apc1, uint8_t *response) {
    return apc1_uart_read(&apc1->uart, response);
}
