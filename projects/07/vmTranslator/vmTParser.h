#ifndef _VMTPARSER_H_
#define _VMTPARSER_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#include <stdlib.h>
#include <string.h>
#include "vmTTools.h"

/* Parse the words on the line, and put results in command array
 * returns the number of words read, so if it returns 0 we can
 * go the the next line in main
 * command has to be malloc'd to be size MAX_COMMAND_WORDS
 */
int parse_line(const char* line, VMCommand* p_cmd);

#endif  // _VMTPARSER_H_
