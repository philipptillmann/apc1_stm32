#include "apc1_stm32_io_uart.h"

#define APC1_CMD_SIZE 7     // The size of the command (7 bytes)
#define APC1_RESPONSE_LENGTH 64  // Expected response length (64 bytes)

#define APC1_UART_TIMEOUT_MS  500U

HAL_StatusTypeDef apc1_uart_init(apc1_uart_t *iface, UART_HandleTypeDef *huart) {
    iface->huart = huart;
    return HAL_OK;
}

// Send the 7-byte command and read the 64-byte response
HAL_StatusTypeDef apc1_uart_read(apc1_uart_t *iface, uint8_t *response) {
    uint8_t command[APC1_CMD_SIZE] = {0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71};  // 7-byte command
    // Step 1: Send the 7-byte command to the sensor
    if (HAL_UART_Transmit(iface->huart, command, APC1_CMD_SIZE, HAL_MAX_DELAY) != HAL_OK) {
        return HAL_ERROR;  // Return error if sending the command failed
    }

    // Step 2: Receive the 64-byte response from the sensor
    if (HAL_UART_Receive(iface->huart, response, APC1_RESPONSE_LENGTH, APC1_UART_TIMEOUT_MS) != HAL_OK) {
        return HAL_ERROR;  // Return error if receiving the response failed
    }

    return HAL_OK;  // Successfully read the data
}

uint16_t apc1_get_pm1_0(uint8_t *response) {
    // Convert the two bytes (0x04, 0x05) to PM1.0 value
    return (response[0x04] << 8) | response[0x05];
}

uint16_t apc1_get_pm2_5(uint8_t *response) {
    // Convert the two bytes (0x06, 0x07) to PM2.5 value
    return (response[0x06] << 8) | response[0x07];
}

uint16_t apc1_get_pm10(uint8_t *response) {
    // Convert the two bytes (0x08, 0x09) to PM10 value
    return (response[0x08] << 8) | response[0x09];
}

uint16_t apc1_get_eco2(uint8_t *response) {
    // Convert the two bytes (0x1E, 0x1F) to eCO2 value (in ppm)
    return (response[0x1E] << 8) | response[0x1F];
}

uint16_t apc1_get_tvoc(uint8_t *response) {
    // Convert the two bytes (0x1C, 0x1D) to TVOC value (in ppb)
    return (response[0x1C] << 8) | response[0x1D];
}

float apc1_get_comp_temperature(uint8_t *response) {
    // Convert the two bytes (0x26, 0x27) to temperature value (in °C)
    uint16_t comp_temp = (response[0x22] << 8) | response[0x23];
    return comp_temp * 0.1f;  // Convert to degrees Celsius (according to the datasheet)
}

float apc1_get_comp_humidity(uint8_t *response) {
    // Convert the two bytes (0x28, 0x29) to humidity value (in %)
    uint16_t comp_humidity = (response[0x24] << 8) | response[0x25];
    return comp_humidity * 0.1f;  // Convert to percentage
}

float apc1_get_raw_temperature(uint8_t *response) {
    // Convert the two bytes (0x26, 0x27) to temperature value (in °C)
    uint16_t raw_temp = (response[0x26] << 8) | response[0x27];
    return raw_temp * 0.1f;  // Convert to degrees Celsius (according to the datasheet)
}

float apc1_get_raw_humidity(uint8_t *response) {
    // Convert the two bytes (0x28, 0x29) to humidity value (in %)
    uint16_t raw_humidity = (response[0x28] << 8) | response[0x29];
    return raw_humidity * 0.1f;  // Convert to percentage
}
