#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int fall = 0;
volatile int rise = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {
        fall = 1; // fall edge
    } else if (events == 0x8) {
        rise = 1; // rise edge
    }
}

int main() {
    stdio_init_all();
    const int BTN_PIN_R = 28;

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_set_irq_enabled_with_callback(
        BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    while (true) {
        if (fall) {
            printf("fall \n");
            fall = 0;
        }
        if (rise) {
            printf("rise \n");
            rise = 0;
        }
    }
}
