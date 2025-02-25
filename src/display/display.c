#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware/i2c.h"
#include "../inc/ssd1306.h"
#include "../inc/font.h"
#include "display.h"

void init_display(ssd1306_t *ssd)
{
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa e configura o display OLED
    ssd1306_init(ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(ssd);
    ssd1306_send_data(ssd);

    // Limpa o display
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

void draw_score(ssd1306_t *ssd, int score)
{
    char score_msg[20];
    snprintf(score_msg, sizeof(score_msg), "Pontuacao: %d", score);

    // Atualiza o display
    ssd1306_fill(ssd, false);
    ssd1306_rect(ssd, 3, 3, 122, 58, true, false);
    ssd1306_draw_string(ssd, score_msg, 8, 28);
    ssd1306_send_data(ssd);
}

void interpretacao_do_caractere(ssd1306_t *ssd, char caractere)
{
    char mensagem[20];
    if ((caractere >= 'A' && caractere <= 'Z') || (caractere >= 'a' && caractere <= 'z'))
    {
        snprintf(mensagem, sizeof(mensagem), "Caractere: %c", caractere);
    }
    else if (caractere >= '0' && caractere <= '9')
    {
        snprintf(mensagem, sizeof(mensagem), "Numero: %c", caractere);
    }
    else
    {
        snprintf(mensagem, sizeof(mensagem), "Outro: %c", caractere);
    }

    // Atualiza o display
    ssd1306_fill(ssd, false);
    ssd1306_rect(ssd, 3, 3, 122, 58, true, false);
    ssd1306_draw_string(ssd, mensagem, 8, 32);
    ssd1306_send_data(ssd);
}

void draw_content_nunb(ssd1306_t *ssd, const char *msg)

{ // Atualiza o display
    ssd1306_fill(ssd, false);
    ssd1306_rect(ssd, 3, 3, 122, 58, true, false);
    ssd1306_draw_string(ssd, (char *)msg, 8, 28);
    ssd1306_send_data(ssd);
}