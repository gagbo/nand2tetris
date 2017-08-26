#include "HackInstruction.h"

// Implementation of the Instruction class

void set_AInstruction(HackInstruction* instr, int16_t address) {
    instr->instruct[0] = 0;
    tobin(address, 15, instr->instruct + 1);
}

void set_CInstruction(HackInstruction* instr, char* dest, char* comp,
                      char* jump) {
    instr->instruct[0] = 1;
    instr->instruct[1] = 1;
    instr->instruct[2] = 1;

    // Dest handling
    if (dest == NULL) {
        instr->instruct[10] = 0;
        instr->instruct[11] = 0;
        instr->instruct[12] = 0;
    } else {
        if (strchr(dest, 'A') != NULL) {
            instr->instruct[10] = 1;
        } else {
            instr->instruct[10] = 0;
        }
        if (strchr(dest, 'D') != NULL) {
            instr->instruct[11] = 1;
        } else {
            instr->instruct[11] = 0;
        }
        if (strchr(dest, 'M') != NULL) {
            instr->instruct[12] = 1;
        } else {
            instr->instruct[12] = 0;
        }
    }

    // Comp handling
    if (strchr(comp, 'M') != NULL) {
        instr->instruct[3] = 1;
    } else {
        instr->instruct[3] = 0;
    }
    if (strcmp(comp, "0") == 0) {
        tobin(42, 6, instr->instruct + 4);
    } else if (strcmp(comp, "1") == 0) {
        tobin(63, 6, instr->instruct + 4);
    } else if (strcmp(comp, "-1") == 0) {
        tobin(58, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D") == 0) {
        tobin(12, 6, instr->instruct + 4);
    } else if (strcmp(comp, "A") == 0 || strcmp(comp, "M") == 0) {
        tobin(48, 6, instr->instruct + 4);
    } else if (strcmp(comp, "!D") == 0) {
        tobin(13, 6, instr->instruct + 4);
    } else if (strcmp(comp, "!A") == 0 || strcmp(comp, "!M") == 0) {
        tobin(49, 6, instr->instruct + 4);
    } else if (strcmp(comp, "-D") == 0) {
        tobin(15, 6, instr->instruct + 4);
    } else if (strcmp(comp, "-A") == 0 || strcmp(comp, "-M") == 0) {
        tobin(51, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D+1") == 0) {
        tobin(31, 6, instr->instruct + 4);
    } else if (strcmp(comp, "A+1") == 0 || strcmp(comp, "M+1") == 0) {
        tobin(55, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D-1") == 0) {
        tobin(14, 6, instr->instruct + 4);
    } else if (strcmp(comp, "A-1") == 0 || strcmp(comp, "M-1") == 0) {
        tobin(50, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "D+M") == 0) {
        tobin(2, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D-A") == 0 || strcmp(comp, "D-M") == 0) {
        tobin(19, 6, instr->instruct + 4);
    } else if (strcmp(comp, "A-D") == 0 || strcmp(comp, "M-D") == 0) {
        tobin(7, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D&A") == 0 || strcmp(comp, "D&M") == 0) {
        tobin(0, 6, instr->instruct + 4);
    } else if (strcmp(comp, "D|A") == 0 || strcmp(comp, "D|M") == 0) {
        tobin(21, 6, instr->instruct + 4);
    }

    // Jump handling
    if (jump == NULL) {
        tobin(0, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JGT") == 0) {
        tobin(1, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JEQ") == 0) {
        tobin(2, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JGE") == 0) {
        tobin(3, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JLT") == 0) {
        tobin(4, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JNE") == 0) {
        tobin(5, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JLE") == 0) {
        tobin(6, 3, instr->instruct + 13);
    } else if (strcmp(jump, "JMP") == 0) {
        tobin(7, 3, instr->instruct + 13);
    }
}

void printInstruction(HackInstruction* instr) {
    for (int i = 0; i <= 15; ++i) {
        printf("%d", instr->instruct[i]);
    }
    printf("\n");
}
