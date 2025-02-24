#ifndef _MATRIZ_H
#define _MATRIZ_H

#include <stdint.h>

#define IS_RGBW false
#define WS2812_PIN 7
#define NUM_PIXELS 25

#define MATRIX_WIDTH 5  // Largura da matriz
#define MATRIX_HEIGHT 5 // Altura da matriz

// Função para colocar um pixel no LED correspondente
void put_pixel(uint32_t pixel_grb);
void put_pixel_at(int x, int y, uint32_t pixel_grb);
uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void increase_color_intensity();
void update_snake();
void update_led_buffer();
void set_leds_from_buffer();

#endif