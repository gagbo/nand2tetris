#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define JGT 1
#define JEQ 2
#define JGE 3
#define JLT 4
#define JNE 5
#define JLE 6
#define JMP 7
#define M 1
#define D 2
#define MD 3
#define A 4
#define AM 5
#define AD 6
#define AMD 7

typedef struct Instructions Instruction;

Instruction convertStringToInstruction(char *AssemblyLine);
// Converts num to it's 16 bit binary representation, and puts it in str
void getBin(int16_t num, char *str);
void tobinstr(int16_t value, int bitsCount, char *output);
