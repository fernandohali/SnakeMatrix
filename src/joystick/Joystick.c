#include "joystick.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Função de inicialização do joystick
void init_joystick()
{
    adc_init();
    adc_gpio_init(JOYSTICK_X);
    adc_gpio_init(JOYSTICK_Y);
    adc_select_input(0); // Eixo X
    adc_select_input(1); // Eixo Y
}

// Função para ler o valor do eixo X
int read_joystick_x()
{
    adc_select_input(0); // Seleciona o eixo X
    return adc_read();   // Lê o valor do eixo X
}

// Função para ler o valor do eixo Y
int read_joystick_y()
{
    adc_select_input(1); // Seleciona o eixo Y
    return adc_read();   // Lê o valor do eixo Y
}