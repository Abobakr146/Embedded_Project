#include "LCD.h"


/*************
=> Initialize the LCD (enable and setup ports)
=> void arguments and return
*************/
void LCD_init(){

    GPIO_PORT_Init(PB);
    GPIO_PORT_Init(PE);

    // Control Pins (RS => PE1, RW => GND, E => PE3)
    GPIO_PORTE_DIR_R |= 0x0A;
    GPIO_PORTE_DEN_R |= 0X0A;
    GPIO_PORTE_AFSEL_R &= ~(0x0E);
    GPIO_PORTE_PCTL_R &= ~(0x0E);
    GPIO_PORTE_AMSEL_R &= ~(0x0E);

    // Data Pins (D0-D7 => PB0-PB7)
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_PCTL_R = 0;
    GPIO_PORTB_AMSEL_R = 0;
    GPIO_PORTB_DEN_R = 0XFF;

    // Set port direction (input or output) and send commands to clear the screen on start
    #if (dataBitsMode == 8)
        GPIO_PORTB_DIR_R = 0xFF;
        LCD_command(eight_bits_two_lines_mode);
    #elif (dataBitsMode == 4)
        GPIO_PORTB_DIR_R |= 0x0F;
        LCD_command(four_bits_two_lines_mode);
    #endif
    LCD_command(cursor_off); // turn off cursor
    LCD_clearScreen(); // clear LCD screen on start
}

/*************
=> Send commands to the LCD
=> argument: command built in the LCD as hex code, defined in "LCD.h" file
=> void return
*************/
void LCD_command(uint8 cmd){

    // disable RS and enable E (LCD)
    GPIO_PORTE_DATA_R &= ~(1<<1);
    delay_ms(1);
    GPIO_PORTE_DATA_R |= 1<<3;
    delay_ms(1);

    // send the command to LCD
    GPIO_PORTB_DATA_R = cmd;
    delay_ms(1);

    // disable E (LCD)
    GPIO_PORTE_DATA_R &= ~(1<<3);
    delay_ms(1);
}


/*************
=> Clear LCD screen
=> void arguments and return
*************/
void LCD_clearScreen(){
    LCD_command(clear_screen);
}


/*************
=> Display single character on LCD screen
=> argument: Character to be displayed
=> void return
*************/
void LCD_displayCharacter(uint8 data){

    // Enable RS and E
    GPIO_PORTE_DATA_R |= 1<<1;
    delay_ms(1);
    GPIO_PORTE_DATA_R |= 1<<3;
    delay_ms(1);

    // Display character
    GPIO_PORTB_DATA_R = data;
    delay_ms(1);

    // Disable E
    GPIO_PORTE_DATA_R &= ~(1<<3);
    delay_ms(1);
}


/*************
=> Display string of characters on LCD screen
=> argument: Constant String address
=> void return
*************/
void LCD_displayString(const uint8 *data){
    uint8 index = 0;
    while(data[index] != '\0'){
        LCD_displayCharacter(data[index]);
        index++;
    }
}
