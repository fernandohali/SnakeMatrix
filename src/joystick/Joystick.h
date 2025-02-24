#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "pico/stdlib.h"

/* Definição dos pinos do Joystick */

#define JOYSTICK_X 26
#define JOYSTICK_Y 27

void init_joystick();
int read_joystick_x();
int read_joystick_y();

#endif