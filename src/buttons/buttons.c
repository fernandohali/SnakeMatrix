#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"
#include <stdio.h>
#include "buttons.h"

// Função de inicialização dos botões
void init_buttons()
{
    gpio_init(BUTTON_A);             // Inicializa o pino do botão
    gpio_set_dir(BUTTON_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_A);          // Habilita o resistor de pull-up

    // Configura a interrupção para o botão
    gpio_set_irq_enabled(BUTTON_A, GPIO_IRQ_EDGE_FALL, true); // Interrupção na borda de descida (botão pressionado)
    gpio_set_irq_callback(button_irq_handler);                // Define o callback da interrupção
    irq_set_enabled(IO_IRQ_BANK0, true);                      // Habilita interrupções do GPIO
}

// Manipulador de interrupção para os botões
void button_irq_handler(uint gpio, uint32_t events)
{
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL))
    {
        printf("Botão A pressionado. Reiniciando no modo bootloader...\n");
        reset_usb_boot(0, 0); // Reinicia no modo bootloader
    }
}