#ifndef HELPER_H_
#define HELPER_H_

#include "std_types.h"
#include "GPS_interface.h"

#define floating_precision 15
#define radius 15

extern void intToStr(uint32 num, uint8* str, uint8* index);
extern void floatToStr(float64 num, uint8* str, uint8 precision);




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
#define     HallAB_Lat1          30.064192333333341
#define     HallAB_Long1         31.280297333333336

#define     HallAB_Lat2          30.064016333333331
#define     HallAB_Long2         31.280385166666679

#define     HallAB_Lat3          30.063919333333341
#define     HallAB_Long3         31.280258166666673

#define     HallAB_Lat4          30.064083500000005
#define     HallAB_Long4         31.280064333333331






// Hall C array of coordinates
#define     HallCD_Lat1          30.063877833333336
#define     HallCD_Long1         31.280349166666670

#define     HallCD_Lat2          30.063717500000006
#define     HallCD_Long2         31.280730333333334

#define     HallCD_Lat3          30.063576166666674
#define     HallCD_Long3         31.280254500000008





// Credit array of coordinates
#define     Credit_Lat1          30.063673999999998
#define     Credit_Long1         31.278485999999997

#define     Credit_Lat2          30.063228166666664
#define     Credit_Long2         31.278603666666661

#define     Credit_Lat3          30.063602666666671
#define     Credit_Long3         31.278225833333340



// Main building array of coordinates
#define     Main_Lat1            30.064928166666671
#define     Main_Long1           31.278127833333329

#define     Main_Lat2            30.064528333333342
#define     Main_Long2           31.278762666666661

#define     Main_Lat3            30.065081666666667
#define     Main_Long3           31.279787166666665



// Concrete array of coordinates
#define     Concrete_Lat1        30.064241833333344
#define     Concrete_Long1       31.278190833333336

#define     Concrete_Lat2        30.064453166666673
#define     Concrete_Long2       31.277973166666665

#define     Concrete_Lat3        30.064330833333336
#define     Concrete_Long3       31.277920666666666

#define     Concrete_Lat4        30.058179000000002
#define     Concrete_Long4       31.275048166666660



// Playgrounds array of coordinates
#define     Playgrounds_Lat1     30.063711666666669
#define     Playgrounds_Long1    31.279007499999995

// #define     Playgrounds_Lat2     0
// #define     Playgrounds_Long2    0

// #define     Playgrounds_Lat3     0
// #define     Playgrounds_Long3    0



//Mosque array of coordinates
#define     Mosque_Lat1          30.064541000000001
#define     Mosque_Long1         31.280157166666672

#define     Mosque_Lat2          30.065021166666671
#define     Mosque_Long2         31.280097500000003

// #define     Mosque_Lat3          0
// #define     Mosque_Long3         0



//Library array of coordinates
#define     Library_Lat1         30.065215166666675
#define     Library_Long1        31.279992999999997

#define     Library_Lat2         30.065108500000004
#define     Library_Long2        31.280214000000000

// #define     Library_Lat3         0
// #define     Library_Long3        0



//Fountain array of coordinates
#define     Fountain_Lat1        30.065631333333332
#define     Fountain_Long1       31.278481499999990

// #define     Fountain_Lat2        0
// #define     Fountain_Long2       0

// #define     Fountain_Lat3        0
// #define     Fountain_Long3       0



#endif
