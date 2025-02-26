#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SNAKE_LENGTH 4 // Tamanho máximo da cobra
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5

typedef struct
{
    int x;
    int y;
} SnakeSegment;

extern int snakeLength;
extern int score; // Declaração da variável score como extern
extern SnakeSegment snake[MAX_SNAKE_LENGTH]; // Array para armazenar a posição dos segmentos da cobra
extern int foodX, foodY;

void init_snake();
void move_snake(int dx, int dy);
int check_collision();
int check_food();
void generate_food();
void update_snake();
void clear_matrix();

#endif