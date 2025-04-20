#include "apc1_stm32_io_uart.h"

#define APC1_CMD_READ 0x04  //tbd
#define APC1_RESPONSE_LENGTH 64

HAL_StatusTypeDef apc1_uart_interface_init(apc1_uart_interface_t *iface, UART_HandleTypeDef *huart) {
    iface->huart = huart;
    return HAL_OK;
}

HAL_StatusTypeDef apc1_uart_interface_read(apc1_uart_interface_t *iface, float *co2, float *temp, float *hum) {
    uint8_t command = APC1_CMD_READ;
    uint8_t response[APC1_RESPONSE_LENGTH];

    if (HAL_UART_Transmit(iface->huart, &command, 1, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    if (HAL_UART_Receive(iface->huart, response, sizeof(response), HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    // Dummy decoding logic
    *co2 = ((response[0] << 8) | response[1]) * 1.0f;
    *temp = ((response[2] << 8) | response[3]) * 0.01f;
    *hum = ((response[4] << 8) | response[5]) * 0.01f;

    return HAL_OK;
}
