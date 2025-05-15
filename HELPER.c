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


    uint8 isHallAB(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat1, HallAB_Long1, radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat2, HallAB_Long2, radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat3, HallAB_Long3, radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallAB_Lat4, HallAB_Long4, radius)
    ) return 1;
    return 0;
}

uint8 isHallCD(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat1, HallCD_Long1, radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat2, HallCD_Long2, radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, HallCD_Lat3, HallCD_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isCredit(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat1, Credit_Long1, radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat2, Credit_Long2, radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Credit_Lat3, Credit_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isMain(float64 GPS_currlat, float64 GPS_currlong){
    if(GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat1, Main_Long1, radius) ||
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat2, Main_Long2, radius) || 
       GPS_isWithinRadius(GPS_currlat, GPS_currlong, Main_Lat3, Main_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isConcrete(float64 GPS_currlat, float64 GPS_currlong){
    if(   GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat1, Concrete_Long1, radius)
       || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat2, Concrete_Long2, radius)
       || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat3, Concrete_Long3, radius)
       || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Concrete_Lat4, Concrete_Long4, radius)
    ) return 1;
    return 0;
}

uint8 isPlaygrounds(float64 GPS_currlat, float64 GPS_currlong){
    if(      GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat1, Playgrounds_Long1, radius) 
       // || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat2, Playgrounds_Long2, radius)  
       // || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Playgrounds_Lat3, Playgrounds_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isMosque(float64 GPS_currlat, float64 GPS_currlong){
    if(   GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat1, Mosque_Long1, radius) 
       || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat2, Mosque_Long2, radius) 
       //|| GPS_isWithinRadius(GPS_currlat, GPS_currlong, Mosque_Lat3, Mosque_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isLibrary(float64 GPS_currlat, float64 GPS_currlong){
    if(   GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat1, Library_Long1, radius)
       || GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat2, Library_Long2, radius) 
       // GPS_isWithinRadius(GPS_currlat, GPS_currlong, Library_Lat3, Library_Long3, radius)
    ) return 1;
    return 0;
}

uint8 isFountain(float64 GPS_currlat, float64 GPS_currlong){
    if(   GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat1, Fountain_Long1, radius)
       //|| GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat2, Fountain_Long2, radius)
       // GPS_isWithinRadius(GPS_currlat, GPS_currlong, Fountain_Lat3, Fountain_Long3, radius)
    ) return 1;
    return 0;
}
