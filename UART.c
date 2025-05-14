 #include "UART.h"

static void GPIO_SetupUART0Pins(void) {
    SYSCTL_RCGCGPIO_R  |= 0x01;
    while(!(SYSCTL_PRGPIO_R & 0x01));   
   
    GPIO_PORTA_AMSEL_R &= 0xFC;         
    GPIO_PORTA_DIR_R   &= 0xFE;         
    GPIO_PORTA_DIR_R   |= 0x02;         
    GPIO_PORTA_AFSEL_R |= 0x03;         
    
    GPIO_PORTA_PCTL_R  = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_R   |= 0x03;         
}

void UART0_Init(void) {
    
    GPIO_SetupUART0Pins();
    
    SYSCTL_RCGCUART_R |= 0x01;
    while(!(SYSCTL_PRUART_R & 0x01));
    
    UART0_CTL_R = 0;

    UART0_CC_R  = 0;
    
    
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    
    
    UART0_LCRH_R = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);
    
    
    UART0_CTL_R = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
}
       
void UART0_SendByte(uint8 data){
    while(!(UART0_FR_R & UART_FR_TXFE_MASK)); 
    UART0_DR_R = data; 
}

uint8 UART0_ReceiveByte(void){
    while(UART0_FR_R & UART_FR_RXFE_MASK); 
    return UART0_DR_R; 
}

void UART0_SendString(const uint8 *pData){
    uint32 uCounter =0;
	
    while(pData[uCounter] != '\0'){
        UART0_SendByte(pData[uCounter]); 
        uCounter++; 
    }
}

void UART0_ReceiveString(uint8 *pData){
    uint16 length = 0;
    uint8 temp;
    while(1){
        temp = UART0_ReceiveByte();
        if(temp == '\0' || temp == '\n' || temp == '\r')
            break;
        pData[length] = temp;
        length++;
    }
    pData[length] = '\0';
}

void UART0_SendInteger(sint64 sNumber){

    uint8 uDigits[20];
    sint8 uCounter = 0;

    
    if (sNumber < 0){
        UART0_SendByte('-');
        sNumber *= -1;
    }
    do{
        uDigits[uCounter++] = sNumber % 10 + '0'; 
        sNumber /= 10; 
    }
    while (sNumber != 0);
    for( uCounter--; uCounter>= 0; uCounter--){
        UART0_SendByte(uDigits[uCounter]);
    }
}

/////////////////////////////////////UART5

static void GPIO_SetupUART5Pins(void){
    SYSCTL_RCGCGPIO_R  |= 1<<4;         
    while(!(SYSCTL_PRGPIO_R & (1<<4)));   
   
    GPIO_PORTE_AMSEL_R &= 0xCF;         
    GPIO_PORTE_DIR_R   &= ~(1<<5);         
    GPIO_PORTE_DIR_R   |= 1<<4;         
    GPIO_PORTE_AFSEL_R |= 0x30;         
    
    GPIO_PORTE_PCTL_R  = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000;
    GPIO_PORTE_DEN_R   |= 0x30;        
}

void UART5_Init(void) {
    
    GPIO_SetupUART5Pins();
    
    SYSCTL_RCGCUART_R |= 0x20;         
    while(!(SYSCTL_PRUART_R & 0x20));   
    
    UART5_CTL_R = 0;                    

    UART5_CC_R  = 0;                    
    
    
    UART5_IBRD_R = 104;
    UART5_FBRD_R = 11;
    
    
    UART5_LCRH_R = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);
    
    
    UART5_CTL_R = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
}
       
void UART5_SendByte(uint8 data){
    while(!(UART5_FR_R & UART_FR_TXFE_MASK)); 
    UART5_DR_R = data; 
}

uint8 UART5_ReceiveByte(void){
    while(UART5_FR_R & UART_FR_RXFE_MASK); 
    return UART5_DR_R; 
}

void UART5_SendString(const uint8 *pData){
    uint32 uCounter =0;
    while(pData[uCounter] != '\0'){
        UART5_SendByte(pData[uCounter]);
        uCounter++; 
    }
}

void UART5_ReceiveString(uint8 *pData){
    uint16 length = 0;
    uint8 temp;
    while(1){
        temp = UART5_ReceiveByte();
        if(temp == '\0' || temp == '\n' || temp == '\r')
            break;
        pData[length] = temp;
        length++;
    }
    pData[length] = '\0';
}

void UART5_SendInteger(sint64 sNumber){
    uint8 uDigits[20];
    sint8 uCounter = 0;
    if (sNumber < 0){
        UART5_SendByte('-');
        sNumber *= -1;
    }
    do{
        uDigits[uCounter++] = sNumber % 10 + '0'; 
        sNumber /= 10; 
    }
    while (sNumber != 0);
    for( uCounter--; uCounter>= 0; uCounter--){
        UART5_SendByte(uDigits[uCounter]);
    }
}
