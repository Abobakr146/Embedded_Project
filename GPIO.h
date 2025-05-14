#ifndef GPIO_H
#define GPIO_H

#include "tm4c123gh6pm.h"
#include "std_types.h"

typedef enum{
    PA, PB, PC, PD, PE, PF
}PORT;

extern void GPIO_Init(void);
extern void GPIO_PORT_Init(PORT port);
extern void GPS_GPIO_Init(void);
extern void Button_GPIO_Init(void);
extern void GPIO_PORTF_Init(void);
extern void LED_On(void);
extern void LED_Off(void);

extern void BUZZ_On(void);
extern void BUZZ_Off(void);
extern boolean Button_Pressed(uint8 var);

#endif
