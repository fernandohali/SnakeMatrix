#include "snake.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include "../matriz/matriz.h"

// Definições das variáveis compartilhadas
int snakeLength = 1;                  // Comprimento inicial da cobra (1 segmento)
int score = 0;                        // Pontuação inicial
SnakeSegment snake[MAX_SNAKE_LENGTH]; // Array para armazenar a posição dos segmentos da cobra
int foodX = -1, foodY = -1;           // Posição da comida

void init_snake()
{
    // Gera uma posição aleatória para a cabeça da cobra
    snake[0].x = rand() % MATRIX_WIDTH;
    snake[0].y = rand() % MATRIX_HEIGHT;

    // Inicializa o restante da cobra com valores inválidos (serão preenchidos ao mover a cobra)
    for (int i = 1; i < MAX_SNAKE_LENGTH; i++)
    {
        snake[i].x = -1;
        snake[i].y = -1;
    }

    // Define o comprimento inicial da cobra
    snakeLength = 1;
}

void move_snake(int dx, int dy)
{
    // Verifica se a cobra comeu a comida
    if (check_food())
    {
        // Aumenta a pontuação
        score++;

        // Aumenta o tamanho da cobra (se não atingiu o tamanho máximo)
        if (snakeLength < MAX_SNAKE_LENGTH)
        {
            // Adiciona um novo segmento na posição da cauda da cobra
            snake[snakeLength] = snake[snakeLength - 1];
            snakeLength++;
        }

        // Gera uma nova comida
        generate_food();
    }

    // Desloca todos os segmentos para frente
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    // Atualiza a posição do segmento cabeça da cobra
    snake[0].x += dx;
    snake[0].y += dy;

    // Verifica se a cobra ultrapassou os limites da matriz
    if (snake[0].x < 0)
        snake[0].x = MATRIX_WIDTH - 1;
    if (snake[0].x >= MATRIX_WIDTH)
        snake[0].x = 0;
    if (snake[0].y < 0)
        snake[0].y = MATRIX_HEIGHT - 1;
    if (snake[0].y >= MATRIX_HEIGHT)
        snake[0].y = 0;
}

int check_collision()
{
    // Verifica se a cobra bateu nas bordas
    if (snake[0].x < 0 || snake[0].x >= MATRIX_WIDTH || snake[0].y < 0 || snake[0].y >= MATRIX_HEIGHT)
    {
        return 1;
    }

    // Verifica se a cobra colidiu com ela mesma
    for (int i = 1; i < snakeLength; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            return 1;
        }
    }

    return 0;
}

int check_food()
{
    if (snake[0].x == foodX && snake[0].y == foodY)
    {
        // A cobra comeu a comida
        return 1;
    }
    return 0;
}

void generate_food()
{
    int valid = 0;
    while (!valid)
    {
        foodX = rand() % MATRIX_WIDTH;
        foodY = rand() % MATRIX_HEIGHT;

        valid = 1;
        for (int i = 0; i < snakeLength; i++)
        {
            if (snake[i].x == foodX && snake[i].y == foodY)
            {
                valid = 0; // A comida está em cima da cobra, gere uma nova posição
                break;
            }
        }
    }
}

void update_snake()
{
    // Desenha a cobra
    for (int i = 0; i < snakeLength; i++)
    {
        int x = snake[i].x;
        int y = snake[i].y;
        uint8_t color_intensity = (uint8_t)(255 * (i / (float)MAX_SNAKE_LENGTH));
        put_pixel_at(x, y, urgb_u32(0, color_intensity, 0)); // Cor verde
    }

    // Desenha a comida
    put_pixel_at(foodX, foodY, urgb_u32(255, 0, 0)); // Cor vermelha
}