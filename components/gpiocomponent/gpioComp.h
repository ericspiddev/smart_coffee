#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_MAX 35
#define TAG "GPIO LIB"

bool configGPIO(uint64_t pin, gpio_mode_t mode, gpio_pullup_t isPullup, gpio_pulldown_t isPulldown, gpio_int_type_t interrupt);