#ifndef TIMER_H
#define TIMER_H

#include "common.h"


static u32int tick = 0;

void init_timer(u32int frequency);
void timer_wait(int n);

#endif
