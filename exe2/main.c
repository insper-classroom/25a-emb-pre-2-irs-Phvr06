#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int fall = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {
      fall = 1; // fall edge
  }
}

int main() {
    stdio_init_all();
    const int BTN_PIN_R = 28;
    const int LED = 4;

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(
        BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    int led_state = 0;
    while (true) {
      if (fall) {
        led_state = !led_state;
        gpio_put(LED, led_state);
        fall = 0;
      }
    }
}
