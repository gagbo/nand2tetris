#ifndef HACKPARSER_H_
#define HACKPARSER_H_
#define LINE_BUFFERSIZE 256

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HackInstructionList.h"
#include "HackSymbolTable.h"

uint32_t symbolless_stream_to_machine_code(FILE* filestream,
                                           HackInstructions* list,
                                           HackSymbolTable* table);
uint32_t parser_labels_pass(FILE* filestream, HackSymbolTable* table);

#endif  // HACKPARSER_H_
