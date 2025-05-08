#include "Systick_Timer.h"
#define SYSTEM_CLK_FREQ 16000000

void systick_init(void)
{
    NVIC_ST_CTRL_R = 0x00;
    NVIC_ST_RELOAD_R = 0x00FFFFFF;
    NVIC_ST_CURRENT_R = 0x00;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_CLK_SRC;
}

void systick_wait_1s(void)
{
    NVIC_ST_RELOAD_R = SYSTEM_CLK_FREQ - 1;
    NVIC_ST_CURRENT_R = 0x00;
    while((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0x00);
}

void systick_wait_1ms(void)
{
    NVIC_ST_RELOAD_R = (SYSTEM_CLK_FREQ / 1000) - 1;
    NVIC_ST_CURRENT_R = 0x00;
    while((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0x00);
}

void delay_ms(uint8 time)
{
    while(time--){
        systick_wait_1ms();
    }
}
