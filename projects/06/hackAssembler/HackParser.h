#ifndef HACKPARSER_H_
#define HACKPARSER_H_
#define LINE_BUFFERSIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HackInstructionList.h"

uint32_t symbolless_stream_to_machine_code(FILE* filestream,
                                           HackInstructions* list);

#endif  // HACKPARSER_H_
