#include "GPIO.h"

void GPIO_Init(void){
    GPIO_PORT_Init(PB);
    GPIO_PORT_Init(PE);
    GPIO_PORT_Init(PF);
    GPS_GPIO_Init();
    Button_GPIO_Init();
    LED_GPIO_Init();
}

void GPIO_PORT_Init(PORT port){
    SYSCTL_RCGCGPIO_R |= 1<<port; 
    while((SYSCTL_PRGPIO_R & 1<<port) == 0);
    switch(port){
        case(PA):
            GPIO_PORTA_DIR_R = 0x00;
            GPIO_PORTA_DEN_R = 0xFF;
            GPIO_PORTA_AMSEL_R = 0x00;
            GPIO_PORTA_AFSEL_R = 0x00;
            GPIO_PORTA_PCTL_R = 0x00000000;
            break;
        case(PB):
            GPIO_PORTB_DIR_R = 0x00;
            GPIO_PORTB_DEN_R = 0xFF;
            GPIO_PORTB_AMSEL_R = 0x00;
            GPIO_PORTB_AFSEL_R = 0x00;
            GPIO_PORTB_PCTL_R = 0x00000000;
            break;
        case(PC):
            GPIO_PORTC_DIR_R = 0x00;
            GPIO_PORTC_DEN_R = 0xFF;
            GPIO_PORTC_AMSEL_R = 0x00;
            GPIO_PORTC_AFSEL_R = 0x00;
            GPIO_PORTC_PCTL_R = 0x00000000;
            break;
        case(PD):
            GPIO_PORTD_DIR_R = 0x00;
            GPIO_PORTD_DEN_R = 0xFF;
            GPIO_PORTD_AMSEL_R = 0x00;
            GPIO_PORTD_AFSEL_R = 0x00;
            GPIO_PORTD_PCTL_R = 0x00000000;
            break;
        case(PE):
            GPIO_PORTE_DIR_R = 0x00;
            GPIO_PORTE_DEN_R = 0xFF;
            GPIO_PORTE_AMSEL_R = 0x00;
            GPIO_PORTE_AFSEL_R = 0x00;
            GPIO_PORTE_PCTL_R = 0x00000000;
            break;
        case(PF):
            GPIO_PORTF_DIR_R = 0x00;
            GPIO_PORTF_DEN_R = 0xFF;
            GPIO_PORTF_AMSEL_R = 0x00;
            GPIO_PORTF_AFSEL_R = 0x00;
            GPIO_PORTF_PCTL_R = 0x00000000;
            break;
        default:
            break;
    }
}

// ========== GPS UART5: PE4 (RX), PE5 (TX) ==========
void GPS_GPIO_Init(void){
    GPIO_PORTE_DIR_R &= ~0x10;  // PE4 = RX = input
    GPIO_PORTE_DIR_R |= 0x20;   // PE5 = TX = output
    GPIO_PORTE_DEN_R |= 0x30;
    GPIO_PORTE_AMSEL_R &= ~0x30;
    GPIO_PORTE_AFSEL_R |= 0x30;
    GPIO_PORTE_PCTL_R &= ~0x00FF0000;
    GPIO_PORTE_PCTL_R |=  0x00110000;
}

// ========== Push Button: PF4 ==========
void Button_GPIO_Init(void){
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x10;
    GPIO_PORTF_DIR_R &= ~0x10;  // PF4 input
    GPIO_PORTF_DEN_R |= 0x10;
    GPIO_PORTF_PUR_R |= 0x10;
    GPIO_PORTF_AMSEL_R &= ~0x10;
    GPIO_PORTF_AFSEL_R &= ~0x10;
    GPIO_PORTF_PCTL_R &= ~0x000F0000;
}

// ========== LED: PF1 ==========
void LED_GPIO_Init(void){
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x02;
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;
    GPIO_PORTF_AMSEL_R &= ~0x02;
    GPIO_PORTF_AFSEL_R &= ~0x02;
    GPIO_PORTF_PCTL_R &= ~0x00000F00;
}

void LED_On(void){
    GPIO_PORTF_DATA_R |= 0x02;
}

void LED_Off(void){
    GPIO_PORTF_DATA_R &= ~0x02;
}

boolean Button_Pressed(void){
    return (GPIO_PORTF_DATA_R & 0x10) == 0;
}
