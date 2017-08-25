#ifndef HACKASSEMBLER_H_
#define HACKASSEMBLER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct Instructions Instruction;

Instruction convertStringToInstruction(char* AssemblyLine);
// Converts num to it's 16 bit binary representation, and puts it in str
void getBin(int16_t num, char* str);
void tobinstr(int16_t value, int bitsCount, char* output);
#endif  // HACKASSEMBLER_H_
