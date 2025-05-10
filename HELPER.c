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
