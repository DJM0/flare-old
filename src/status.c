#include <board.h>
#include <gpio.h>

#include "status.h"

#define STATUS_SLEEP_TIME 500

#define STATUS_LED_0 LED0_GPIO_PORT
#define STATUS_LED_PIN_0 LED0_GPIO_PIN
#define STATUS_LED_1 LED2_GPIO_PORT
#define STATUS_LED_PIN_1 LED2_GPIO_PIN

#define STATUS_STACK_SIZE 500
#define STATUS_PRIORITY 5

K_THREAD_STACK_DEFINE(status_thread_stack_area, STATUS_STACK_SIZE);

static struct k_thread status_thread_data;

void thread(void *a, void *b, void *c)
{

    u8_t cnt = 0;
    struct device *led_0;
    struct device *led_1;

    led_0 = device_get_binding(STATUS_LED_0);
    led_1 = device_get_binding(STATUS_LED_1);

    gpio_pin_configure(led_0, STATUS_LED_PIN_0, GPIO_DIR_OUT);
    gpio_pin_configure(led_1, STATUS_LED_PIN_1, GPIO_DIR_OUT);

      while (1) {

          gpio_pin_write(led_0, STATUS_LED_PIN_0, cnt % 2);
          gpio_pin_write(led_1, STATUS_LED_PIN_1, cnt % 2 - 1);

          cnt++;

          k_sleep(STATUS_SLEEP_TIME);

      }

}

void status_init()
{

    k_thread_create(
        &status_thread_data, status_thread_stack_area,
        K_THREAD_STACK_SIZEOF(status_thread_stack_area),
        thread,
        NULL, NULL, NULL,
        STATUS_PRIORITY, 0, K_NO_WAIT);

}
