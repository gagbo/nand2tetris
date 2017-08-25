#ifndef HACKASSEMBLER_H_
#define HACKASSEMBLER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Instruction Instruction;
struct Instruction {
    // line Number or Address of instruction in ROM
    uint32_t lineNumber;
    Instruction* next;

    // Concat these from top to bottom to get
    // instruction from LSB[15] to MSB[0]
    bool instruct[16];
    // 1 wide
    bool* aOrC;
    // 2 wide
    bool* c1s;
    // 1 wide
    bool* aOrM;
    // 6 wide
    bool* alu;
    // 3 wide
    bool* destination;
    // 3 wide
    bool* jump;
};
typedef Instruction* Instructions;

// Sets the instruction instr to be an A instruction pointing to address
// Note, address is a 15-bit uint, so an in16_t is perfect to check for
// errors and there's no need to use a 16-bit unsigned int
void set_AInstruction(Instruction* instr, int16_t address);

// Sets the instruction instr to be a C instruction using dest(ination),
// comp(utation) and jump (condition).
// Any of the strings may be empty, but the caller has to make sure at least
// one string is not.
// Also the string in dest, comp and jump must be uppercase without any space
void set_CInstruction(Instruction* instr, char* dest, char* comp, char* jump);

void printInstruction(Instruction* instr);

// Converts num to it's 16 bit binary representation, and puts it in str
void getBin(int16_t num, char* str);
void tobinstr(int16_t value, int bitsCount, char* output);
#endif  // HACKASSEMBLER_H_
