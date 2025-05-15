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
extern void LED_GPIO_Init(void);
extern void GPIO_PORTF_Init(void); //modified
extern void LED_On(void);
extern void LED_Off(void);
extern void BUZZ_On(void); //modified
extern void BUZZ_Off(void); //modified
extern boolean Button_Pressed(void);
extern boolean Button_Pressed_case(uint8 var); //modified

#endif
