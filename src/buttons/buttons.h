#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "pico/types.h"
#include <stdint.h>

#define BUTTON_A 5

void init_buttons(void);
void button_irq_handler(uint gpio, uint32_t events);

#endif