#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "Systick_Timer.h"
#include "GPIO.h"

#ifndef LCD_H_
#define LCD_H_

#define     dataBitsMode                            8
#define     eight_bits_two_lines_mode               0x38
#define     eight_bits_one_line_mode                0x30
#define     four_bits_two_lines_mode                0x28
#define     four_bits_one_line_mode                 0x02
#define     clear_screen                            0x01
#define     set_cursor                              0x80
#define     cursor_off                              0x0C
#define     cursor_on                               0x0E
#define     cursor_blink                            0x0F

// RS => PE1, RW => GND, E => PE3, D0-D7 => PB0-PB7

void LCD_init();
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const uint8 *data);
void LCD_clearScreen();
void LCD_goToRowColumn(uint8 row, uint8 column);
void LCD_command(uint8 cmd);

#endif
