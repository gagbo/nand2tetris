#ifndef HACKTOOLS_H_
#define HACKTOOLS_H_

#include <stdbool.h>
#include <stdint.h>

void getBin(int16_t num, char* str);
void tobinstr(int16_t value, int bitsCount, char* output);
void tobin(int16_t value, int bitscount, bool* output);

#endif  // HACKTOOLS_H_
