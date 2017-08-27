#ifndef HACKPARSER_H_
#define HACKPARSER_H_
#define LINE_BUFFERSIZE 4294967296
#define LABELS_IN_A_ROW_BUFFER 32
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HackInstructionList.h"
#include "HackSymbolTable.h"

uint32_t symbolless_stream_to_machine_code(FILE* filestream,
                                           HackInstructions* p_list,
                                           HackSymbolTable* p_table);
uint32_t parser_labels_pass(FILE* filestream, HackSymbolTable* p_table);

char* strstrip(char* s);

#endif  // HACKPARSER_H_
