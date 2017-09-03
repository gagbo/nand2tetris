#ifndef _VMTWRITER_H_
#define _VMTWRITER_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#define ASM_LINE_BUFFER_SIZE 33
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict/vmTDictFiles.h"

// Struct that keeps the count of label-powered translations to
// produce unique labels during one file translation.
typedef struct LabelCounter {
    int nb_eq;
    int nb_gt;
    int nb_lt;
    int nb_and;
    int nb_or;
    int nb_not;
} LabelCounter;

/* Choose the correct asm file for the translation
 * this function is neither responsible for malloc nor freeing memory
 * for command[i] arrays.
 * Giving the number of words in the command helps the choosing
 * The returned string should NOT be modified, and is ine of the strings in
 * vmTDictFiles.h
 */
const char* choose_asm_dict_file(const char** command, int command_len);

/* Main writer function :
 * filestream : output filestream
 * command : originally parsed command, used to get command[2]
 * p_labelCounter : pointer to LabelCounter struct to make unique labels
 * asm_stub : COPY (caller responsiblity) of the XXX_asm string in vmTDictFiles
 * asm_stub_number : int version of command[2] when applicable, negative
 * otherwise
 * basename : basename of the vm file to produce unique static labels
 */
void write_to_file(FILE* filestream, const char** command,
                   LabelCounter* p_labelCounter, const char* asm_stub,
                   int asm_stub_number, char* basename);

#endif  // _VMTWRITER_H_
