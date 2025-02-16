#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_R = 4;
const int LED_G = 6;

volatile int green = 0;
volatile int red = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        if (gpio == BTN_PIN_R) {
            red = 1;
        }
    }
    if (events == 0x8) {
        if (gpio == BTN_PIN_G) {
            green = 1;
        }
    }
}

int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                       &btn_callback);

    gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

    int led_r_state = 0;
    int led_g_state = 0;
    while (true) {
      if (red) {
        red = 0;
        led_r_state = !led_r_state;
        gpio_put(LED_R, led_r_state);
      }
      if (green) {
        green = 0;
        led_g_state = !led_g_state;
        gpio_put(LED_G, led_g_state);
      }
    }
}
