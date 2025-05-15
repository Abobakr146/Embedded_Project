#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "LCD.h"
#include "UART.h"
#include "GPIO.h"
#include "GPS_interface.h"
#include "Systick_Timer.h"
#include "HELPER.h"

void main(){
    GPIO_Init();
    LCD_init();
    UART0_Init();
    UART5_Init();
    systick_init();
    GPS_GPIO_Init();

    
    while(1) {
        float64 GPS_lat, GPS_long;
        GPS_Status_t status = GPS_getCurrentLocation(&GPS_lat, &GPS_long);
        // //Latitude: ddmm.mmmm  Long: dddmm.mmmm
        uint8 buf[10];
        // // gcvt(GPS_lat, 9, buf);
        //snprintf(buf, sizeof(buf), "%.30f", GPS_lat);
        floatToStr(GPS_lat, buf, floating_precision);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');

        // LCD_goToRowColumn(0,0);
        // LCD_displayString("Lat:");
        // LCD_displayString(buf);

        floatToStr(GPS_long, buf, floating_precision);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');
        
        // LCD_goToRowColumn(1,0);
        // LCD_displayString("Long:");
        // LCD_displayString(buf);

        LCD_clearScreen();
        // LCD_goToRowColumn(0, 0);
        // LCD_displayString("Dest:");
        LCD_goToRowColumn(1, 0);

        if(isHallAB(GPS_lat, GPS_long)){
            LCD_displayString("Halls A,B");
            LED_On();
            BUZZ_On();
        }

        else if(isHallCD(GPS_lat, GPS_long)){
            LCD_displayString("Halls C,D");
            LED_On();
            BUZZ_On();
        }

        else if(isCredit(GPS_lat, GPS_long)){
            LCD_displayString("Credit Building");
            LED_On();
            BUZZ_On();
        }

        else if(isMain(GPS_lat, GPS_long)){
            LCD_displayString("Main Building");
            LED_On();
            BUZZ_On();
        }

        else if(isConcrete(GPS_lat, GPS_long)){
            LCD_displayString("Concrete Building");
            LED_On();
            BUZZ_On();
        }

        else if(isPlaygrounds(GPS_lat, GPS_long)){
            LCD_displayString("Playgrounds");
            LED_On();
            BUZZ_On();
        }

        else if(isMosque(GPS_lat, GPS_long)){
            LCD_displayString("Mosque");
            LED_On();
            BUZZ_On();
        }

        else if(isLibrary(GPS_lat, GPS_long)){
            LCD_displayString("Library");
            LED_On();
            BUZZ_On();
        }

        else if(isFountain(GPS_lat, GPS_long)){
            LCD_displayString("Fountain");
            LED_On();
            BUZZ_On();
        }
        else{
            LCD_displayString("None");
            LED_On();
            BUZZ_Off();
        }

    }

}
