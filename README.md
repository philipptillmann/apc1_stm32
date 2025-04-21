# APC1 STM32 Driver Library

This is an unofficial lightweight C library for the ScioSense APC1 air quality sensor, designed for STM32 microcontrollers. The library provides an easy-to-use abstraction for UART communication, with future support planned for I2C.

---

## Features

- 📡 UART communication (HAL-based)
- 💨 CO2, temperature, and humidity measurement
- ⚡ Simple and clean API
- 💾 Easy to extend with I2C or other transport layers
- 🧪 Suitable for bare-metal or RTOS-based STM32 projects

---

## Directory Structure

```
apc1-stm32-driver/
├── LICENSE               # License file (MIT)
├── README.md             # This file
├── src/
│   ├── apc1_stm32.c
│   ├── apc1_stm32_io_uart.c
│   └── apc1_stm32_io_i2c.c (future)
├── include/
│   ├── apc1_stm32.h
│   ├── apc1_stm32_defines.h
│   ├── apc1_stm32_io_uart.h
│   └── apc1_stm32_io_i2c.h (future)
├── utils/
│   └── apc1_crc.c (to be commited)
│   └── apc1_crc.h (to be commited)
├── examples/
|   └── stm32_UART/
|       └── main.c   
└── test/
    └── test_apc1.c (to be commited)
```

---

## Usage Example

```c
#include "apc1_stm32.h"

apc1_stm32_t apc1;
apc1_stm32_init_uart(&apc1, &huart1);

// Read the response
if (apc1_uart_read(&apc1, response) == HAL_OK) {
    // Get specific values from the response
    uint16_t pm10 = apc1_get_pm10(response);
    uint16_t eco2 = apc1_get_eco2(response);
    uint16_t tvoc = apc1_get_tvoc(response);
    float temp = apc1_get_comp_temperature(response);
    float hum = apc1_get_comp_humidity(response);
}
```

---

## Dependencies

- STM32 HAL drivers
- C99-compatible compiler

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Future Plans

- [ ] Add I2C support

---

## Credits

Inspired by the official ScioSense APC1 Arduino library design (https://github.com/sciosense/apc1-arduino) and adapted for embedded STM32 environments.

