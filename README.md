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
└── test/
    └── test_apc1.c (to be commited)
```

---

## Usage Example

```c
#include "apc1_stm32.h"

apc1_stm32_t apc1;
apc1_stm32_init_uart(&apc1, &huart1);

float co2, temperature, humidity;
if (apc1_stm32_read(&apc1, &co2, &temperature, &humidity) == HAL_OK) {
    // Use the sensor data
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
- [ ] Add CRC check utilities
- [ ] Add platform abstraction to separate STM32 HAL from core logic

---

## Credits

Inspired by the official ScioSense APC1 Arduino library design (https://github.com/sciosense/apc1-arduino) and adapted for embedded STM32 environments.

