#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SNAKE_LENGTH 25

typedef struct
{
    int x;
    int y;
} SnakeSegment;

extern int snakeLength;
extern SnakeSegment snake[MAX_SNAKE_LENGTH];
extern int foodX, foodY;

void init_snake();
void move_snake(int dx, int dy);
int check_collision();
int check_food();
void generate_food();
void update_snake();
void clear_matrix();

#endif