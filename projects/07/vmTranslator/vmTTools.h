#ifndef _VMTTOOLS_H_
#define _VMTTOOLS_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#define MAX_COMMAND_WORDS 3
#define MAX_COMMAND_WORD_LENGTH 256
#define MAX_NUMBER_OF_FILES 30

#include <dirent.h>
#include <libgen.h>  // basename
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct IOFiles {
    FILE **input;
    char **input_filenames;
    FILE *output;
    char *basename;
    int fileCount;
} IOFiles;

IOFiles open_filestreams(const char *filename);
FILE *IOF_open_outputstream(IOFiles *p_ioFiles, const char *filename);
int IOF_open_inputstream(IOFiles *p_ioFiles, const char *filename);
void IOF_set_basename(IOFiles *p_ioFiles, const char *new_basename);

void IOF_clear(IOFiles *p_ioFiles);
void IOF_init(IOFiles *p_ioFiles);
bool IOF_check(IOFiles *p_ioFiles);

typedef struct VMCommand {
    char **command;
    // Current function name.
    char *functionName;
} VMCommand;
void VMC_init(VMCommand *p_vmc);
void VMC_clear(VMCommand *p_vmc);
void VMC_set_function_name(VMCommand *p_vmc, char *newFunctionName);

#endif  // _VMTTOOLS_H_
