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
        //snprintf(buf, sizeof(buf), "%.5f", GPS_lat);
        floatToStr(GPS_lat, buf, 15);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');

        floatToStr(GPS_long, buf, 15);
        UART0_SendString(buf);  // Forward to UART0 (PC terminal)
        UART0_SendByte('\n');  // Forward to UART0 (PC terminal)
        UART0_SendByte('\r');
        
    }

}
