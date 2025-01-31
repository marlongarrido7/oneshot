#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_BLUE_PIN   12  // LED azul
#define LED_RED_PIN    13  // LED vermelho
#define LED_GREEN_PIN  11  // LED verde
#define BUTTON_PIN      5  // Botão A

#define DEBOUNCE_DELAY_MS 200   // Tempo de debounce (200ms)
#define TIMER_DELAY_MS    3000  // Atraso de 3 segundos entre as mudanças de estado

volatile bool sequence_running = false;  // Impede nova ativação antes do ciclo terminar
volatile absolute_time_t last_press_time;  // Para controle de debounce

// 🔹 Prototipação das funções antes do uso (corrige erro de declaração)
int64_t turn_off_red(alarm_id_t id, void *user_data);
int64_t turn_off_green(alarm_id_t id, void *user_data);

// Callback do temporizador: Desliga o LED azul
int64_t turn_off_blue(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE_PIN, 0);
    printf("LED Azul desligado.\n");
    add_alarm_in_ms(TIMER_DELAY_MS, turn_off_red, NULL, false);
    return 0;
}

// Callback do temporizador: Desliga o LED vermelho
int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED_PIN, 0);
    printf("LED Vermelho desligado.\n");
    add_alarm_in_ms(TIMER_DELAY_MS, turn_off_green, NULL, false);
    return 0;
}

// Callback do temporizador: Desliga o LED verde e finaliza a sequência
int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN_PIN, 0);
    sequence_running = false; // Permite nova ativação
    printf("LED Verde desligado. Sequência finalizada.\n");
    return 0;
}

// ISR do botão com debounce
void button_isr(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    
    if (absolute_time_diff_us(last_press_time, now) / 1000 < DEBOUNCE_DELAY_MS) {
        return; // Ignora múltiplos acionamentos rápidos (bouncing)
    }

    if (!sequence_running) {
        sequence_running = true; // Bloqueia novas ativações
        last_press_time = now;

        // Liga todos os LEDs
        gpio_put(LED_BLUE_PIN, 1);
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_GREEN_PIN, 1);
        printf("Botão pressionado! Iniciando sequência...\n");

        // Inicia a sequência de desligamento após 3s
        add_alarm_in_ms(TIMER_DELAY_MS, turn_off_blue, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs como saída
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_put(LED_BLUE_PIN, 0);

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_put(LED_RED_PIN, 0);

    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, 0);

    // Configuração do botão com pull-up interno
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, button_isr);

    while (1) {
        sleep_ms(100);  // Aguarda para reduzir uso de CPU
    }
}
