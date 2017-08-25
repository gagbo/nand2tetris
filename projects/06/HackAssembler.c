#include "HackAssembler.h"

// For the time being, we aim to translate a file stripped of whitespaces, and
// free of symbols. Handling files to get to this point will be done in another
// module

int main(int argc, char **argv) {
    // 1) Open the file or throw error
    char filename[50];
    if (argc > 2) {
        printf("Too many arguments supplied.\n");
        return 1;
    } else if (argc <= 1) {
        printf("One argument expected.\n");
        return 1;
    } else {
        strcpy(filename, argv[1]);
    }
    char str[17];
    tobinstr(12452, 16, str);
    printf("%s %s\n", str, filename);
    // 1) Translate the line into an Instruction and print it
    return 0;
}

struct Instructions {
    // line Number or Address of instruction in ROM
    uint32_t lineNumber;
    Instruction *next;

    // Concat these from top to bottom to get
    // instruction from MSB to LSB
    bool aOrC;
    bool c1s[2];
    bool aOrM;
    bool alu[6];
    bool destination[3];
    bool jump[3];
};

// Not sure how it works yet, especially the while condition so left aside.
void getBin(int16_t num, char *str) {
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
void tobinstr(int16_t value, int bitsCount, char *output) {
    int i;
    output[bitsCount] = '\0';
    for (i = bitsCount - 1; i >= 0; --i, value >>= 1) {
        output[i] = !!(value & 1) + '0';
    }
}
