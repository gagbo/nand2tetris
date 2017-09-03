#ifndef _VMTMAIN_H_
#define _VMTMAIN_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#define LINE_BUFFERSIZE 256

#include <libgen.h>  // basename
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "vmTParser.h"
#include "vmTWriter.h"

typedef struct IOFiles {
    FILE *input;
    FILE *output;
    char *basename;
} IOFiles;

IOFiles open_filestreams(const char *filename);
void IOF_clear(IOFiles *p_ioFiles);
void IOF_init(IOFiles *p_ioFiles);
bool IOF_check(IOFiles *p_ioFiles);

#endif  // _VMTMAIN_H_
