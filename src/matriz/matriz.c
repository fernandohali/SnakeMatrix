#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "../snake/snake.h"
#include "../../generated/ws2812.pio.h"
#include "matriz.h"

// Variáveis globais para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t selected_led = 0;              // Índice do LED a ser controlado (0 a 24)
uint8_t led_r = 50;                    // Valor inicial para vermelho
uint8_t led_g = 50;                    // Valor inicial para verde
uint8_t led_b = 50;                    // Valor inicial para azul
uint32_t led_buffer[NUM_PIXELS] = {0}; // Buffer para armazenar as cores de todos os LEDs

// Implementações das funções
void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

void put_pixel_at(int x, int y, uint32_t pixel_grb)
{
    int index = y * MATRIX_WIDTH + x; // Mapeia coordenadas (x, y) para o índice do LED
    led_buffer[index] = pixel_grb;    // Atualiza o buffer de LEDs
    put_pixel(pixel_grb);             // Envia o pixel para a matriz de LEDs
}

uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

void update_led_buffer()
{
    // Apaga todos os LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        led_buffer[i] = 0; // Desliga todos os LEDs
    }

    // Desenha a cobra
    for (int i = 0; i < snakeLength; i++)
    {
        int x = snake[i].x;
        int y = snake[i].y;
        int index = y * MATRIX_WIDTH + x;
        led_buffer[index] = urgb_u32(0, 255, 0); // Cor verde para a cobra
    }

    // Desenha a comida
    int foodIndex = foodY * MATRIX_WIDTH + foodX;
    led_buffer[foodIndex] = urgb_u32(255, 0, 0); // Cor vermelha para a comida
}

void set_leds_from_buffer()
{
    // Envia o estado de todos os LEDs para a matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        put_pixel(led_buffer[i]);
    }
}

void increase_color_intensity()
{
    if (led_r < 255)
        led_r += 10;
    if (led_g < 255)
        led_g += 10;
    if (led_b < 255)
        led_b += 10;
}