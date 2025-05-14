#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_

#include "std_types.h"



//Constants
#define PI 3.14159265358979323846
#define EARTH_RADIUS_M 6371000

//size of GPS Sentence
#define MAX_SENTENCE_FEILDS 15
#define SENTENCE_SIZE 100


typedef enum {
    GPS_NO_DATA = 0,
    GPS_VALID_DATA = 1,
    GPS_INVALID_DATA = 2,
} GPS_Status_t;

extern float64 GPS_ConvertToDecimalDegrees(float64 coordinatesInGPSformat);

extern float64 GPS_degreesToRadians(float64 degree);

extern float64 GPS_getDistance_angleInDegrees(float64 GPS_lat, float64 GPS_long, float64 GPS_latSaved, float64 GPS_lonSaved);

extern GPS_Status_t GPS_readNMEASentence(uint8* NMEA_buffer);

extern GPS_Status_t GPS_getCurrentLocation(float64* GPS_lat, float64* GPS_long);

extern GPS_Status_t GPS_getCurrentLocationWithTimeout(float64* GPS_lat, float64* GPS_long, uint16 timeout);

extern uint8 GPS_isWithinRadius(float64 currLatitude, float64 currLongitude, float64 targetLatitude, float64 targetLongitude, float64 targetRadius);

extern float64 stof(uint8 *str);


extern uint8* customStrtok_r(uint8* str, const uint8* delim, uint8** saveptr);

#endif


