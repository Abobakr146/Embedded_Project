#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H
#include "tm4c123gh6pm.h"
#include "std_types.h"

void systick_init(void);
void systick_wait_1s(void);
void systick_wait_1ms(void) ;
void delay_ms(uint8 time);

#endif
