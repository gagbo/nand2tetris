#include "HackTools.h"

// Not sure how it works yet, especially the while condition so left aside.
void getBin(int16_t num, char* str) {
    // Ensure that the string won't be read after the 16th bit
    *(str + 16) = '\0';
    // Create a mask that is a single 1, shifted to the left to
    // compensate the first while instruction
    long mask = 0x10 << 1;

    while (mask >>= 1) *str++ = !!(mask & num) + '0';
}

// Simpler to understand implementation :
// The value to convert is bitwise AND-ed to 1 to get and write the LSB
// then value is right-shifted so the new LSB of value is actually the next LSB
// of previous value
void tobinstr(int16_t value, int bitscount, char* output) {
    int i;
    output[bitscount] = '\0';
    for (i = bitscount - 1; i >= 0; --i, value >>= 1) {
        output[i] = !!(value & 1) + '0';
    }
}
void tobin(int16_t value, int bitscount, bool* output) {
    int i;
    for (i = bitscount - 1; i >= 0; --i, value >>= 1) {
        output[i] = !!(value & 1);
    }
}
