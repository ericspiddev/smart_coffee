#include <stdio.h>
#include "timerComp.h"
#include "gpioComp.h"
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

volatile unsigned int tog = 0;
gptimer_handle_t gptimer = NULL;
static bool toggle(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    tog ^= 1;
    gpio_set_level(GPIO_NUM_23, tog);
    return true;
}

void app_main(void)
{
    configGPIO(23, GPIO_MODE_OUTPUT, 0, 0, GPIO_INTR_DISABLE);
    gpio_config_t gpioConfig = {
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 1 << 23,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
    };

    gpio_config(&gpioConfig);
    gpio_set_level(GPIO_NUM_23, tog);

    gptimer_config_t gpConfig = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1 * 1000 * 1000
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&gpConfig, &gptimer));

    // ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    ESP_ERROR_CHECK(gptimer_enable(gptimer));
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 60000000,
        .reload_count = 0,
        .flags.auto_reload_on_alarm = true,
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));

    ESP_ERROR_CHECK(gptimer_start(gptimer));


    while(1)
    {
        vTaskDelay(1);
    }
}


