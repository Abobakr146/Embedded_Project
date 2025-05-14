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

    uint8 destinationArrayIndex = 0;
    
    while(1) {


        if(Button_Pressed()){
            delay_ms(125);
            destinationArrayIndex++;
            destinationArrayIndex %= sizeof(destinations) / sizeof(destinations[0]);
        }


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


        floatToStr(GPS_long, buf, 130);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');
        


        LCD_clearScreen();
        LCD_goToRowColumn(0, 0);
        LCD_displayString("Dest:");
        destinationStatus_t destinationStatus = ledBlinkerAndDestinationDisplayer(destinations[destinationArrayIndex], GPS_lat, GPS_long);
        LCD_goToRowColumn(1, 0);





        if(isHallAB(GPS_lat, GPS_long)){
            LCD_displayString("Halls A,B");
        }

        else if(isHallCD(GPS_lat, GPS_long)){
            LCD_displayString("Halls C,D");
        }

        else if(isCredit(GPS_lat, GPS_long)){
            LCD_displayString("Credit Building");
        }

        else if(isMain(GPS_lat, GPS_long)){
            LCD_displayString("Main Building");
        }

        else if(isConcrete(GPS_lat, GPS_long)){
            LCD_displayString("Concrete Building");
        }

        else if(isPlaygrounds(GPS_lat, GPS_long)){
            LCD_displayString("Playgrounds");
        }

        else if(isMosque(GPS_lat, GPS_long)){
            LCD_displayString("Mosque");
        }

        else if(isLibrary(GPS_lat, GPS_long)){
            LCD_displayString("Library");
        }

        else if(isFountain(GPS_lat, GPS_long)){
            LCD_displayString("Fountain");
        }
        else{
            LCD_displayString("None");
        }

    }

}
