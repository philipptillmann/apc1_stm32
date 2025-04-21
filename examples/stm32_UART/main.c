#include "stm32f4xx_hal.h"

// UART handle
UART_HandleTypeDef huart2;

// APC1
apc1_stm32_t apc1;

// 7-byte request to send
uint8_t request[7] = {0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71};

// Buffer for 64-byte response
uint8_t response[64];

// Function prototypes
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_USART1_UART_Init();

   // One‐time sensor init
   if (apc1_stm32_init_uart(&apc1, &huart1) != HAL_OK) {
       // Handle init error (blink an LED, etc.)
   }

   uint8_t response[APC1_RESPONSE_LENGTH];

  /* Infinite loop */
  while (1)
  {
	  // Read the response
	  if (apc1_uart_read(&apc1, response) == HAL_OK) {
	      // Get specific values from the response
	      uint16_t pm1_0 = apc1_get_pm1_0(response);
	      uint16_t pm2_5 = apc1_get_pm2_5(response);
	      uint16_t pm10 = apc1_get_pm10(response);
	      uint16_t eco2 = apc1_get_eco2(response);
	      uint16_t tvoc = apc1_get_tvoc(response);
	      float temp = apc1_get_comp_temperature(response);
	      float hum = apc1_get_comp_humidity(response);

	      // Now you can use these values for further processing or output
	      printf("PM1.0: %d ug/m3, PM2.5: %d ug/m3, PM10: %d ug/m3\n", pm1_0, pm2_5, pm10);
	      printf("eCO2: %d ppm, TVOC: %d ppb\n", eco2, tvoc);
	      printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temp, hum);
	  } else {
	      // Handle error
	      printf("Error reading from the sensor.\n");
	  }

      HAL_Delay(1000);  // Read once per second

  }
}

void SystemClock_Config(void) {
    // Configure the system clock (simplified for example)
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void MX_GPIO_Init(void) {
    // Initialize GPIO (if needed for UART pins)
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3; // PA2: TX, PA3: RX
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void MX_USART2_UART_Init(void) {
    // Initialize UART2
    __HAL_RCC_USART2_CLK_ENABLE();

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}