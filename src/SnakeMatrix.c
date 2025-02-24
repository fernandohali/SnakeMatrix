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

        // Leitura do joystick e atualização da posição
        int x_value = read_joystick_x();
        int y_value = read_joystick_y();

        printf("Joystick X: %d, Y: %d\n", x_value, y_value);

        // Calcula a direção do movimento da cobra
        int dx = 0, dy = 0;

        // Mapeamento correto dos eixos do joystick
        if (x_value > 3000)
        { // Movimento para cima
            printf("Movimento para cima\n");
            printf("Joystick X: %d, Y: %d\n", x_value, y_value);
            dx = 0;
            dy = 1;
        }
        else if (x_value < 1000)
        { // Movimento para baixo
            printf("Movimento para baixo\n");
            printf("Joystick X: %d, Y: %d\n", x_value, y_value);
            dx = 0;
            dy = -1;
        }
        else if (y_value < 1000)
        { // Movimento para a esquerda
            printf("Movimento para a esquerda\n");
            printf("Joystick X: %d, Y: %d\n", x_value, y_value);
            dx = 1;
            dy = 0;
        }
        else if (y_value > 3000)
        { // Movimento para a direita
            printf("Movimento para a direita\n");
            dx = -1;
            dy = 0;
        }
    
        // Move a cobra
        move_snake(dx, dy);

        // Verifica se a cobrinha comeu a comida
        if (check_food())
        {
            increase_color_intensity(); // Aumenta a intensidade da cor
            generate_food();            // Gera uma nova comida
        }

        // Atualiza a cobrinha na matriz de LEDs
        clear_matrix();
        update_snake();

        // Verifica se a cobra colidiu
        if (check_collision())
        {
            printf("Game Over\n");
            sleep_ms(1000);  // Espera 1 segundo antes de reiniciar
            init_snake();    // Reinicializa a cobra
            generate_food(); // Gera uma nova comida
            snakeLength = 1; // Reinicia o comprimento da cobra
        }

        sleep_ms(200); // Delay para o loop
    }

    return 0;
}