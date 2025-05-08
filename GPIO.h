#include "tm4c123gh6pm.h"
#include "std_types.h"

#ifndef GPIO_H
#define GPIO_H

typedef enum{
    PA, PB, PC, PD, PE, PF
}PORT;

void GPIO_Init(void);
void GPIO_PORT_Init(PORT port);
void GPS_GPIO_Init(void);
void Button_GPIO_Init(void);
void LED_GPIO_Init(void);
void LED_On(void);
void LED_Off(void);
boolean Button_Pressed(void);

#endif
