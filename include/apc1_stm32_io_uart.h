#ifndef APC1_STM32_IO_UART_H_
#define APC1_STM32_IO_UART_H_

#include "stm32h7xx_hal.h" // Adjust this include based on your STM32 series

typedef struct {
    UART_HandleTypeDef *huart;
} apc1_uart_t;

// Function to initialize the UART interface
HAL_StatusTypeDef apc1_uart_init(apc1_uart_t *iface, UART_HandleTypeDef *huart);

// Function to send a command and read the response from the sensor
HAL_StatusTypeDef apc1_uart_read(apc1_uart_t *iface, uint8_t *response);

// Getter functions for specific data from the 64-byte response
uint16_t apc1_get_pm1_0(uint8_t *response);  // Get PM1.0
uint16_t apc1_get_pm2_5(uint8_t *response);  // Get PM2.5
uint16_t apc1_get_pm10(uint8_t *response);   // Get PM10
uint16_t apc1_get_eco2(uint8_t *response);   // Get eCO2
uint16_t apc1_get_tvoc(uint8_t *response);   // Get TVOC
float apc1_get_comp_temperature(uint8_t *response);  // Get Compensated Temperature
float apc1_get_comp_humidity(uint8_t *response);     // Get Compensated Humidity
float apc1_get_raw_temperature(uint8_t *response);  // Get Raw Temperature
float apc1_get_raw_humidity(uint8_t *response);     // Get Raw Humidity

#endif
