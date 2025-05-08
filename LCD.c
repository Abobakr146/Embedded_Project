#include "LCD.h"


/*************
=> Initialize the LCD (enable and setup ports)
=> void arguments and return
*************/
void LCD_init(){

    // Enable ports B and E
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOE;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R) == 0); //delay (wait) till SYSCTL is enabled

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
    LCD_command(clear_screen); // clear LCD screen on start
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
// (Existing code for LCD_init, LCD_command, LCD_clearScreen,
//  LCD_displayCharacter, LCD_displayString should be above this)

/*************
=> Go to specific row and column on LCD screen
=> arguments: row (0 or 1 for a 2-line LCD), column (0 to 15 for a 16x2 LCD)
=> void return
*************/


void LCD_goToRowColumn(uint8 row, uint8 column) {
    uint8 address;

   
    if (column > 15) { // Prevent writing past the end of a 16-column line
        column = 15;
    }

    // Calculate DDRAM address based on row
    // For 2-line displays: Row 0 starts at 0x00, Row 1 at 0x40

    switch (row) {
        case 0:
            address = column;
            break;
        case 1:
            address = column + 0x40;
            break;
       // Add cases for 4-line displays if needed (e.g., row 2 at 0x10/0x14, row 3 at 0x50/0x54)
        default:
          
            address = column;// Default to row 0 if row is invalid

            break;
    }

    // Send the command to set the DDRAM address.
    LCD_command(set_cursor | address);
}
