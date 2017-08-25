#include "HackAssembler.h"

// For the time being, we aim to translate a file stripped of whitespaces, and
// free of symbols. Handling files to get to this point will be done in another
// module

int main(int argc, char** argv) {
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
    FILE* filestream = NULL;
    char line[256];
    char str[17];
    tobinstr(12452, 16, str);
    printf("%s %s\n", str, filename);
    // 1) Translate the line into an Instruction and print it
    filestream = fopen(filename, "r");
    while (fgets(line, 255, filestream) != NULL) {
        // Do stuff to parse the file
        // Strip line from white space
        // See if line[0] is @
        // a) if it is, then Ainstruction
        // b) else, parse for C instruction
    }
    return 0;
}

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

void set_AInstruction(Instruction* instr, int16_t address) {
    instr->instruct[15] = 0;
    tobin(address, 15, instr->instruct);
}

void set_CInstruction(Instruction* instr, char* dest, char* comp, char* jump) {
    instr->instruct[15] = 1;
    instr->instruct[14] = 1;
    instr->instruct[13] = 1;

    // Dest handling
    if (strchr(dest, 'A') != NULL) {
        instr->instruct[5] = 1;
    } else {
        instr->instruct[5] = 0;
    }
    if (strchr(dest, 'D') != NULL) {
        instr->instruct[4] = 1;
    } else {
        instr->instruct[4] = 0;
    }
    if (strchr(dest, 'M') != NULL) {
        instr->instruct[3] = 1;
    } else {
        instr->instruct[3] = 0;
    }

    // Comp handling
    if (strchr(comp, 'M') != NULL) {
        instr->instruct[12] = 1;
    } else {
        instr->instruct[12] = 0;
    }
    if (strcmp(comp, "0") == 0) {
        tobin(42, 6, instr->instruct + 6);
    } else if (strcmp(comp, "1") == 0) {
        tobin(63, 6, instr->instruct + 6);
    } else if (strcmp(comp, "-1") == 0) {
        tobin(58, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D") == 0) {
        tobin(12, 6, instr->instruct + 6);
    } else if (strcmp(comp, "A") == 0 || strcmp(comp, "M") == 0) {
        tobin(48, 6, instr->instruct + 6);
    } else if (strcmp(comp, "!D") == 0) {
        tobin(13, 6, instr->instruct + 6);
    } else if (strcmp(comp, "!A") == 0 || strcmp(comp, "!M") == 0) {
        tobin(49, 6, instr->instruct + 6);
    } else if (strcmp(comp, "-D") == 0) {
        tobin(15, 6, instr->instruct + 6);
    } else if (strcmp(comp, "-A") == 0 || strcmp(comp, "-M") == 0) {
        tobin(51, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D+1") == 0) {
        tobin(31, 6, instr->instruct + 6);
    } else if (strcmp(comp, "A+1") == 0 || strcmp(comp, "M+1") == 0) {
        tobin(57, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D-1") == 0) {
        tobin(14, 6, instr->instruct + 6);
    } else if (strcmp(comp, "A-1") == 0 || strcmp(comp, "M-1") == 0) {
        tobin(50, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "D+M") == 0) {
        tobin(2, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D-A") == 0 || strcmp(comp, "D-M") == 0) {
        tobin(19, 6, instr->instruct + 6);
    } else if (strcmp(comp, "A-D") == 0 || strcmp(comp, "M-D") == 0) {
        tobin(7, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D&A") == 0 || strcmp(comp, "D&M") == 0) {
        tobin(0, 6, instr->instruct + 6);
    } else if (strcmp(comp, "D|A") == 0 || strcmp(comp, "D|M") == 0) {
        tobin(21, 6, instr->instruct + 6);
    }

    // Jump handling
    if (strcmp(jump, "JGT") == 0) {
        tobin(1, 3, instr->instruct);
    } else if (strcmp(jump, "JEQ") == 0) {
        tobin(2, 3, instr->instruct);
    } else if (strcmp(jump, "JGE") == 0) {
        tobin(3, 3, instr->instruct);
    } else if (strcmp(jump, "JLT") == 0) {
        tobin(4, 3, instr->instruct);
    } else if (strcmp(jump, "JNE") == 0) {
        tobin(5, 3, instr->instruct);
    } else if (strcmp(jump, "JLE") == 0) {
        tobin(6, 3, instr->instruct);
    } else if (strcmp(jump, "JMP") == 0) {
        tobin(7, 3, instr->instruct);
    }
}

void printInstruction(Instruction* instr) {
    for (int i = 15; i >= 0; --i) {
        printf("%d", instr->instruct[i]);
    }
    printf("\n");
}
