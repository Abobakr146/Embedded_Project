#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H
#include "tm4c123gh6pm.h"
#include "std_types.h"

extern void systick_init(void);
extern void systick_wait_1s(void);
extern void systick_wait_1ms(void) ;
extern void delay_ms(uint16 time);

#endif
