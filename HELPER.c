#include "HELPER.h"

// Helper: convert integer to string (from earlier)
void intToStr(uint32 num, uint8* str, uint8* index) {
    uint8 start = *index;

    if (num == 0) {
        str[(*index)++] = '0';
    } else {
        while (num > 0) {
            str[(*index)++] = (num % 10) + '0';
            num /= 10;
        }

        // Reverse the digits
        uint8 end = *index - 1;
        while (start < end) {
            uint8 tmp = str[start];
            str[start] = str[end];
            str[end] = tmp;
            start++;
            end--;
        }
    }
}

void floatToStr(float64 num, uint8* str, uint8 precision) {
    uint8 index = 0;

    // Handle negative numbers
    if (num < 0.0) {
        str[index++] = '-';
        num = -num;
    }

    // Extract integer part
    uint32 intPart = (uint32)num;
    float64 fractional = num - (float64)intPart;

    // Convert integer part to string
    intToStr(intPart, str, &index);

    // Add decimal point
    str[index++] = '.';

    // Process fractional part without rounding
    uint8 i = 0;
    for (; i < precision; i++) {
        fractional *= 10.0;
        uint8 digit = (uint8)fractional;
        str[index++] = digit + '0';
        fractional -= digit;
    }

    // Null-terminate the string
    str[index] = '\0';
}


void ledBlinkerAndDestinationDisplayer(uint8 chosenDest, float64 GPS_currlat, float64 GPS_currlong){

    if(chosenDest == 'A'){
        LCD_displayString("Hall A,B");
    }
    
    else if(chosenDest == 'B'){
        LCD_displayString("Hall C,D");
    }

    else if(chosenDest == 'C'){
        LCD_displayString("Credit");
    }

    else if(chosenDest == 'D'){
        LCD_displayString("Main");
    }

    else if(chosenDest == 'E'){
        LCD_displayString("Concrete");
    }

    else if(chosenDest == 'F'){
        LCD_displayString("Playgrounds");
    }
    else if(chosenDest == 'G'){
        LCD_displayString("Mosque");
    }

    else if(chosenDest == 'H'){
        LCD_displayString("Library");
    }

    else if(chosenDest == 'I'){
        LCD_displayString("Fountain");
    }
    else { 
        LED_Off(); 
        return; 
    }


    range_t range = rangeDecider(chosenDest, GPS_currlat, GPS_currlong);
    if(range == outOfRange) 
        LED_Off();
    else if(range == far) {
        LED_On();
        delay_ms(1000);
        LED_Off();    
        delay_ms(700);
    }
    else if(range == close){
        LED_On();
        delay_ms(500);
        LED_Off();    
        delay_ms(200);
    }
    else if(range == veryClose) {
        LED_On();
    }
    return;
}


range_t rangeDecider(uint8 chosenDest, float64 GPS_currlat, float64 GPS_currlong){
    if(chosenDest == 'A'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, HallAB_Lat[0] , HallAB_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, HallAB_Lat[i] , HallAB_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'B'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, HallCD_Lat[0] , HallCD_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, HallCD_Lat[i] , HallCD_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'C'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Credit_Lat[0] , Credit_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Credit_Lat[i] , Credit_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'D'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Main_Lat[0] , Main_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Main_Lat[i] , Main_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'E'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Concrete_Lat[0] , Concrete_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Concrete_Lat[i] , Concrete_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }
    
    else if(chosenDest == 'F'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Playgrounds_Lat[0] , Playgrounds_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Playgrounds_Lat[i] , Playgrounds_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'G'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Mosque_Lat[0] , Mosque_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Mosque_Lat[i] , Mosque_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'H'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Library_Lat[0] , Library_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Library_Lat[i] , Library_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }

    else if(chosenDest == 'I'){
        float64 min = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Fountain_Lat[0] , Fountain_Long[0]);
        uint8 i = 1;
        for(; i < 3; i++){
            float64 temp = GPS_getDistance_angleInDegrees(GPS_currlat, GPS_currlong, Fountain_Lat[i] , Fountain_Long[i]);
            if(temp < min){
                min = temp;
            }
        }
        if(min > 40) return outOfRange;
        else if (min <= 40 && min > 30) return far;
        else if (min <= 30 && min > 20) return close;
        else if (min <= 20) return veryClose; 
    }
    return NA; 
}


uint8 isHallAB(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat[0], HallAB_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat[1], HallAB_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat[2], HallAB_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isHallCD(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat[0], HallCD_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat[1], HallCD_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat[2], HallCD_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isCredit(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat[0], Credit_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat[1], Credit_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat[2], Credit_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isMain(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat[0], Main_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat[1], Main_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat[2], Main_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isConcrete(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat[0], Concrete_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat[1], Concrete_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat[2], Concrete_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isPlaygrounds(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat[0], Playgrounds_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat[1], Playgrounds_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat[2], Playgrounds_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isMosque(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat[0], Mosque_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat[1], Mosque_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat[2], Mosque_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isLibrary(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat[0], Library_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat[1], Library_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat[2], Library_Long[2], radius)
    ) return 1;
    return 0;
}

uint8 isFountain(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat[0], Fountain_Long[0], radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat[1], Fountain_Long[1], radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat[2], Fountain_Long[2], radius)
    ) return 1;
    return 0;
}


