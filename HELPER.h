#ifndef HELPER_H_
#define HELPER_H_

#include "std_types.h"
#include "LCD.h"
#include "Systick_Timer.h"
#include "GPS_interface.h"
#include "GPIO.h"
//#define precision 15


#define radius 15
#define destinations (uint8[]){'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'} //Array of destination codes, 'J' is "No Destination Specified"

typedef enum {
    outOfRange,
    far,
    close,
    veryClose,
    NA
} range_t;

typedef enum {
    destinationExists,
    noDestination  
} destinationStatus_t;


extern void intToStr(uint32 num, uint8* str, uint8* index);
extern void floatToStr(float64 num, uint8* str, uint8 precision);
extern destinationStatus_t ledBlinkerAndDestinationDisplayer(uint8 chosenDest, float64 GPS_currlat, float64 GPS_currlong);
extern range_t rangeDecider(uint8 chosenDest, float64 GPS_currlat, float64 GPS_currlong);


extern uint8 isHallAB(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isHallCD(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isCredit(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isMain(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isConcrete(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isPlaygrounds(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isMosque(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isLibrary(float64 GPS_currlat, float64 GPS_currlong);
extern uint8 isFountain(float64 GPS_currlat, float64 GPS_currlong);














// Hall A array of coordinates
#define     HallAB_Lat          (float64[]){30.064321833333345, 0, 0} //A
#define     HallAB_Long         (float64[]){31.280189833333345, 0, 0}

// Hall C array of coordinates
#define     HallCD_Lat          (float64[]){30.063794833333336, 0, 0} //B
#define     HallCD_Long         (float64[]){31.280445333333332, 0, 0}

// Credit array of coordinates
#define     Credit_Lat          (float64[]){30.063646333333334, 0, 0} //C
#define     Credit_Long         (float64[]){31.279065666666664, 0, 0}

// Main building array of coordinates
#define     Main_Lat            (float64[]){30.064635833333340, 0, 0} //D
#define     Main_Long           (float64[]){31.278724833333331, 0, 0}

// Concrete array of coordinates
#define     Concrete_Lat        (float64[]){30.064466999999996, 0, 0} //E
#define     Concrete_Long       (float64[]){31.277844666666663, 0, 0}

// Playgrounds array of coordinates
#define     Playgrounds_Lat     (float64[]){30.063711666666669, 0, 0} //F
#define     Playgrounds_Long    (float64[]){31.279007499999995, 0, 0}

//Mosque array of coordinates
#define     Mosque_Lat          (float64[]){30.064685500000010, 0, 0} //G
#define     Mosque_Long         (float64[]){31.280304500000003, 0, 0}

//Library array of coordinates
#define     Library_Lat         (float64[]){30.065210999999997, 0, 0} //H
#define     Library_Long        (float64[]){31.280070500000004, 0, 0}

//Fountain array of coordinates
#define     Fountain_Lat        (float64[]){30.065631333333332, 0, 0} //I
#define     Fountain_Long       (float64[]){31.278481499999990, 0, 0}

#endif
