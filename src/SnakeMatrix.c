#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "joystick/joystick.h"
#include "snake/snake.h"
#include "matriz/matriz.h"

PIO pio = pio0;
int sm = 0;
uint offset;

// Variáveis para armazenar a direção atual da cobra
int dx = 0, dy = 0;

// Variável para controlar a velocidade da cobra
int snake_speed = 500; // Valor inicial do delay (em ms)

int main()
{
    // Inicializações e configurações
    stdio_init_all();
    init_joystick();

    // Inicializa o programa WS2812
    offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Inicializa a cobra
    init_snake();

    // Gera a primeira comida
    generate_food();

    while (true)
    {
        // Atualiza o buffer com o LED e a cor selecionados
        update_led_buffer();

        // Envia o estado do buffer para a matriz
        set_leds_from_buffer();

        // Leitura do joystick e atualização da direção
        int x_value = read_joystick_x();
        int y_value = read_joystick_y();

        printf("Joystick X: %d, Y: %d\n", x_value, y_value);

        // Atualiza a direção da cobra com base no joystick
        if (x_value > 3000)
        { // Movimento para cima
            printf("Movimento para cima\n");
            dx = 0;
            dy = 1;
        }
        else if (x_value < 1000)
        { // Movimento para baixo
            printf("Movimento para baixo\n");
            dx = 0;
            dy = -1;
        }
        else if (y_value < 1000)
        { // Movimento para a esquerda
            printf("Movimento para a esquerda\n");
            dx = 1;
            dy = 0;
        }
        else if (y_value > 3000)
        { // Movimento para a direita
            printf("Movimento para a direita\n");
            dx = -1;
            dy = 0;
        }

        // Move a cobra na direção atual
        move_snake(dx, dy);

        // Verifica se a cobrinha comeu a comida
        if (check_food())
        {
            increase_color_intensity(); // Aumenta a intensidade da cor
            generate_food();            // Gera uma nova comida

            // Aumenta a velocidade da cobra (diminui o delay)
            if (snake_speed > 100) // Define um limite mínimo para o delay
            {
                snake_speed -= 50; // Diminui o delay em 50 ms
            }
        }

        // Verifica se a cobra colidiu
        if (check_collision())
        {
            printf("Game Over\n");
            sleep_ms(1000);  // Espera 1 segundo antes de reiniciar
            init_snake();    // Reinicializa a cobra
            generate_food(); // Gera uma nova comida
            snakeLength = 1; // Reinicia o comprimento da cobra
            dx = 0;          // Reseta a direção
            dy = 0;
            snake_speed = 500; // Reseta a velocidade da cobra
        }

        sleep_ms(snake_speed); // Usa o valor atual de snake_speed para o delay
    }

    return 0;
}