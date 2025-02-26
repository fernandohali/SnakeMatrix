#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "joystick/joystick.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "display/display.h"
#include "snake/snake.h"
#include "matriz/matriz.h"
#include "buttons/buttons.h"

PIO pio = pio0;
int sm = 0;
uint offset;

// Definição do display
ssd1306_t ssd;

// Variáveis para armazenar a direção atual da cobra
int dx = 0, dy = 0;

// Variável para controlar a velocidade da cobra
int snake_speed = 300; // Valor inicial do delay (em ms)

int main()
{
    // Inicializações e configurações
    stdio_init_all();
    init_joystick();

    // Inicializa o gerador de números aleatórios
    srand(time_us_64());

    // Inicializando os módulos
    init_buttons();
    printf("Botões inicializados.\n");

    // Inicializa o display
    init_display(&ssd);

    // Inicializa o programa WS2812
    offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Inicializa a cobra
    init_snake();

    // Gera a primeira comida
    generate_food();

    while (true)
    {
        // Leitura do joystick e atualização da direção
        int x_value = read_joystick_x();
        int y_value = read_joystick_y();

        printf("Joystick X: %d, Y: %d\n", x_value, y_value);

        // Atualiza a direção da cobra com base no joystick
        if (x_value > 3000)
        { // Movimento para cima
            printf("Movimento para cima\n");
            if (dy == 0)
            { // Evita inverter a direção
                dx = 0;
                dy = 1;
            }
        }
        else if (x_value < 1000)
        { // Movimento para baixo
            printf("Movimento para baixo\n");
            if (dy == 0)
            { // Evita inverter a direção
                dx = 0;
                dy = -1;
            }
        }
        else if (y_value < 1000)
        { // Movimento para a esquerda
            printf("Movimento para a esquerda\n");
            if (dx == 0)
            { // Evita inverter a direção
                dx = -1;
                dy = 0;
            }
        }
        else if (y_value > 3000)
        { // Movimento para a direita
            printf("Movimento para a direita\n");
            if (dx == 0)
            { // Evita inverter a direção
                dx = 1;
                dy = 0;
            }
        }

        // Move a cobra na direção atual
        move_snake(dx, dy);

        // Atualiza o buffer com o LED e a cor selecionados
        update_led_buffer();

        // Envia o estado do buffer para a matriz
        set_leds_from_buffer();

        // Exibe a pontuação no display
        draw_score(&ssd, score);

        // Verifica se a cobra colidiu
        if (check_collision())
        {
            // Exibe "Game Over" no display
            draw_content_nunb(&ssd, "Game Over");
            sleep_ms(2000); // Espera 2 segundos antes de reiniciar

            // Reinicializa o jogo
            init_snake();    // Reinicializa a cobra
            generate_food(); // Gera uma nova comida
            snakeLength = 1; // Reinicia o comprimento da cobra
            score = 0;       // Reinicia a pontuação
            dx = 0;          // Reseta a direção
            dy = 0;
            snake_speed = 300; // Reseta a velocidade da cobra
        }

        sleep_ms(snake_speed); // Usa o valor atual de snake_speed para o delay
    }

    return 0;
}