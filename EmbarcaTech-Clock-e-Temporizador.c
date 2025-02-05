#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint LED_RED = 13;
const uint LED_YELLOW = 12;
const uint LED_GREEN = 11;

// STATES OF THE TRAFFIC LIGHT
// ESTADOS DO SEMÁFORO

typedef enum {
    RED,
    YELLOW,
    GREEN
} state_traffic_light_t;

state_traffic_light_t state_now = RED;

bool traffic_light_callback(struct repeating_timer *t){
    gpio_put(LED_RED,0);
    gpio_put(LED_YELLOW,0);
    gpio_put(LED_GREEN,0);

    // TOGGLES TRAFFIC LIGHT STATES
    // ALTERNA OS ESTADOS DO SEMÁFORO
    switch (state_now) {
        case RED:
            gpio_put(LED_RED, 1);
            state_now = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_YELLOW, 1);
            state_now = GREEN;
            break;
        case GREEN:
            gpio_put(LED_GREEN, 1);
            state_now = RED;
            break;
    }
    return true;
}

int main() {

    stdio_init_all();

    // INITIALIZATION OF THE PINS
    //INICIAÇÂO DOS PINOS
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN); 
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
      
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, traffic_light_callback, NULL, &timer); // Alterna a cada 3 segundos

    while (1) {
        tight_loop_contents(); // Mantém o loop rodando
    }
}