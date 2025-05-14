#include <math.h> 
#include <string.h> 
#include <stdlib.h> 

#include "UART.h" 
#include "std_types.h"
#include "GPS_interface.h"

/*
*Longitude & latitude format : ddmm.mmmm d for degree, We will need to transform this to degree format
*This degree format will be converted to radians to be compatiable with the math.h trig functions
*ex. 3007.038 to decimal degrees 30.1173
*/ 

//Function to convert latitude and longitude to decimal degrees 
float64 GPS_ConvertToDecimalDegrees(float64 coordinatesInGPSformat) {
    uint32 GPS_coordinatesDegrees = (uint32)(coordinatesInGPSformat / 100);
    float64 GPS_coordinatesMinutes = coordinatesInGPSformat - (GPS_coordinatesDegrees * 100);
    return GPS_coordinatesDegrees + (GPS_coordinatesMinutes / 60.0);
}// Done

float64 GPS_degreesToRadians(float64 degree) {
    return degree * (PI / 180.0);
}// Done


//The user should give angles in degree format not ddmm.mmmm format 
float64 GPS_getDistance_angleInDegrees(float64 GPS_lat, float64 GPS_long, float64 GPS_latSaved, float64 GPS_lonSaved) {
    float64 GPS_diffLat = GPS_degreesToRadians(GPS_latSaved - GPS_lat);
    float64 GPS_diffLong = GPS_degreesToRadians(GPS_lonSaved - GPS_long);

    GPS_lat = GPS_degreesToRadians(GPS_lat);
    GPS_latSaved = GPS_degreesToRadians(GPS_latSaved);

    float64 temp1 = sin(GPS_diffLat / 2);
    float64 temp2 = cos(GPS_lat);
    float64 temp3 = cos(GPS_latSaved);
    float64 temp4 = sin(GPS_diffLong / 2);

    float64 a = (temp1 * temp1) + (temp2 * temp3 * temp4 * temp4);

    float64 c = 2 * atan2(sqrt(a), sqrt(1 - a)); // atan(y/x) --- atan2(y, x) both are tan inverse in difference format

    return EARTH_RADIUS_M * c;
}// Done


// Function to read a complete NMEA sentence
GPS_Status_t GPS_readNMEASentence(uint8* NMEA_buffer) {
    uint8 bufferChar;
    uint8 NMEA_bufferIndex = 0;
    uint8 NMEA_startFound = 0;

/****************************************************************************************************************************/
    // Clear timeout or add timeout counter if needed
    while (NMEA_bufferIndex < SENTENCE_SIZE - 1) {

        // if (UART_StdErrorReceiveByte(Copy_ptrUartConfig, &bufferChar) != VALID) { //This function still unknown
        //     return GPS_NO_DATA;
        // }

        bufferChar = UART5_ReceiveByte();
/****************************************************************************************************************************/
        
        
        // Look for start of a sentence
        if (bufferChar == '$') {
            NMEA_startFound = 1;
            NMEA_bufferIndex = 0;
        }

        if (NMEA_startFound) {
            NMEA_buffer[NMEA_bufferIndex++] = bufferChar;

            // Check for end of sentence
            if (bufferChar == '\n' || bufferChar == '\r') {
                NMEA_buffer[NMEA_bufferIndex] = '\0';
                return GPS_VALID_DATA;
            }
        }
    }

    // Buffer full without finding complete sentence
    NMEA_buffer[SENTENCE_SIZE - 1] = '\0';
    return GPS_INVALID_DATA;

}// Done - UART Config needed



//This function gets the current coordinates of the GPS in degrees and it uses a function that reads the NMEA sentence which uses UART_ReceiveByteFunction() 
GPS_Status_t GPS_getCurrentLocation(float64* GPS_lat, float64* GPS_long) {
    uint8 NMEA_buffer[SENTENCE_SIZE];
    uint8* local_pu8Token;
    //uint8 Local_u8ValidFlag = 0; Not used till now
    GPS_Status_t Local_Status;
    uint8* savePtr;

    // Try to find a valid GPRMC sentence
    uint8 Local_u8Attempts = 0;
    while (Local_u8Attempts < 15) { // Try up to 5 NMEA sentences
        Local_Status = GPS_readNMEASentence(NMEA_buffer);

        if (Local_Status == GPS_VALID_DATA) {
            // Check if it's a GPRMC sentence --- strstr function to find a substring -- return a point of first occurrence
            if (strstr((char*)NMEA_buffer, "$GPRMC") != NULL_PTR) { //Changed: unit*=8 to char
                break;
            }
        }
        Local_u8Attempts++;
    }

    if (Local_u8Attempts >= 15) {
        return GPS_NO_DATA;
    }
/*****************************************************************************************************************/
    // Tokenize the GPRMC sentence
    // $GPRMC,time,status,latitude,N/S,longitude,E/W,...
    local_pu8Token = customStrtok_r((uint8*)NMEA_buffer, ",", &savePtr); // Skip the $GPRMC part

    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr); // Get time

    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr); // Get status

    // Check if data is valid: 'A' = Valid, 'V' = Invalid
    if (local_pu8Token == NULL_PTR || local_pu8Token[0] != 'A') {
        return GPS_INVALID_DATA;
    }

    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr);
    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    float64 GPS_latTemp = stof((uint8*)local_pu8Token);

    // Get latitude direction (N/S)
    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr);
    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    uint8 GPS_latDirection = local_pu8Token[0];

    // Get longitude value
    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr);
    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    float64 GPS_longTemp = stof((uint8*)local_pu8Token);

    // Get longitude direction (E/W)
    local_pu8Token = customStrtok_r(NULL_PTR, ",", &savePtr);
    if (local_pu8Token == NULL_PTR) return GPS_INVALID_DATA;
    uint8 GPS_longDirection = local_pu8Token[0];

/*****************************************************************************************************************/

    // Convert to decimal degrees
    *GPS_lat = GPS_ConvertToDecimalDegrees(GPS_latTemp);
    *GPS_long = GPS_ConvertToDecimalDegrees(GPS_longTemp);

    // Apply directions
    if (GPS_latDirection == 'S') *GPS_lat = -(*GPS_lat);
    if (GPS_longDirection == 'W') *GPS_long = -(*GPS_long);

    return GPS_VALID_DATA;

}// Done


// Function to wait until valid GPS data is available with timeout
GPS_Status_t GPS_getCurrentLocationWithTimeout(float64* GPS_lat, float64* GPS_long, uint16 timeout) {
    GPS_Status_t GPS_status = GPS_NO_DATA;
    uint16 attempts = 0;

    while (attempts < timeout) {
        GPS_status = GPS_getCurrentLocation(GPS_lat, GPS_long);

        if (GPS_status == GPS_VALID_DATA) {
            return GPS_VALID_DATA;
        }

        attempts++;
    }
    return GPS_status;
}// Done 

// Function to check if the current position is within a certain radius of a target
uint8 GPS_isWithinRadius(float64 currLatitude, float64 currLongitude, float64 targetLatitude, float64 targetLongitude, float64 targetRadius) {
    float64 distanceBetweenCurrAndTarget = GPS_getDistance_angleInDegrees(currLatitude, currLongitude, targetLatitude, targetLongitude);

    return (distanceBetweenCurrAndTarget <= targetRadius) ? 1 : 0;
}//Done


float64 stof(uint8 *str) {
    float64 result = 0.0;
    float64 decimalPlace = 0.1;
    uint8 decimalFound = 0;

    while (*str) {
        if (*str == '.') {
            decimalFound = 1;
        } else if (*str >= '0' && *str <= '9') {
            if (!decimalFound) {
                result = (result * 10) + (*str - '0');
            } else {
                result += (*str - '0') * decimalPlace;
                decimalPlace *= 0.1;
            }
        }
        str++;
    }
    return result;
}// Done


uint8* customStrtok_r(uint8* str, const uint8* delim, uint8** saveptr) {
    uint8* token;

    if (str == NULL_PTR) {
        str = *saveptr;
    }

    // Skip leading delimiters
    str += strspn((char*)str, (char*)delim);
    if (*str == '\0') {
        return NULL_PTR;
    }

    token = str;

    // Find end of token
    str = (uint8*)strpbrk((char*)token, (char*)delim);
    if (str != NULL_PTR) {
        *str = '\0';
        *saveptr = str + 1;
    } else {
        *saveptr = (uint8*)strchr((char*)token, '\0');
    }

    return token;
}

