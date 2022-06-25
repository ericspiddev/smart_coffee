#include "gpioComp.h"

bool configGPIO(uint64_t pin, gpio_mode_t mode, gpio_pullup_t isPullup, gpio_pulldown_t isPulldown, gpio_int_type_t interrupt)
{
    if(pin > PIN_MAX)
    {
        ESP_LOGI(TAG, "Pin is out of range for gpio");
        return false;
    }

   gpio_config_t config = {
        .pin_bit_mask = (1 << pin), //each pin corresponds to a bit
        .mode = mode,
        .pull_up_en = isPullup,
        .pull_down_en = isPulldown,
        .intr_type = interrupt
    };

    return true;
}