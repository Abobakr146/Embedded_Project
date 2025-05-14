#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "LCD.h"
#include "UART.h"
#include "GPIO.h"
#include "GPS_interface.h"
#include "Systick_Timer.h"
#include "HELPER.h"

void main(){
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
        floatToStr(GPS_lat, buf, 130);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');

        // LCD_goToRowColumn(0,0);
        // LCD_displayString("Lat:");
        // LCD_displayString(buf);

        floatToStr(GPS_long, buf, 130);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');
        
        // LCD_goToRowColumn(1,0);
        // LCD_displayString("Long:");
        // LCD_displayString(buf);

        // LCD_goToRowColumn(0, 0);
        // LCD_displayString("Dest:");
        LCD_clearScreen();
        LCD_goToRowColumn(1, 0);

        if(GPS_isWithinRadius(GPS_lat, GPS_long, HallAB_Lat, HallAB_Long, 30)){
            LCD_displayString("Halls A,B");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, HallCD_Lat, HallCD_Long, 30)){
            LCD_displayString("Halls C,D");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Credit_Lat, Credit_Long, 30)){
            LCD_displayString("Credit Building");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Main_Lat, Main_Long, 30)){
            LCD_displayString("Main Building");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Concrete_Lat, Concrete_Long, 30)){
            LCD_displayString("Concrete Building");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Playgrounds_Lat, Playgrounds_Long, 30)){
            LCD_displayString("Playgrounds");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Workshops_Lat, Workshops_Long, 30)){
            LCD_displayString("Workshops");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Arch_Lat, Arch_Long, 30)){
            LCD_displayString("Archeticture");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Cafeteria_Lat, Cafeteria_Long, 30)){
            LCD_displayString("Cafeteria");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Mosque_Lat, Mosque_Long, 30)){
            LCD_displayString("Mosque");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Library_Lat, Library_Long, 30)){
            LCD_displayString("Library");
        }

        else if(GPS_isWithinRadius(GPS_lat, GPS_long, Fountain_Lat, Fountain_Long, 30)){
            LCD_displayString("Fountain");
        }
        else{
            LCD_displayString("None");
        }

    }

}
