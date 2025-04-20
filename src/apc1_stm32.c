#include "apc1_stm32.h"

HAL_StatusTypeDef apc1_stm32_init_uart(apc1_stm32_t *apc1, UART_HandleTypeDef *huart) {
    return apc1_uart_interface_init(&apc1->uart, huart);
}

HAL_StatusTypeDef apc1_stm32_read(apc1_stm32_t *apc1, float *co2, float *temp, float *hum) {
    return apc1_uart_interface_read(&apc1->uart, co2, temp, hum);
}
