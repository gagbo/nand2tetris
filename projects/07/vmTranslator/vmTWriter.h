#ifndef _VMTWRITER_H_
#define _VMTWRITER_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#include <stdio.h>
#include <string.h>

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
 * It's the caller responsibility to allocate and free the memory allocated for
 * the return value of the function
 */
void choose_asm_dict_file(char* filename, const char** command, int wordCount);

/* Main writer function :
 * filestream : output filestream
 * command : originally parsed command
 * p_labelCounter : pointer to LabelCounter struct to make unique labels
 * dict_filename : the name of the dict file to read then write to output
 * basename : basename of the vm file to produce unique static labels
 */
void write_to_file(FILE* filestream, const char** command,
                   LabelCounter* p_labelCounter, char* dict_filename,
                   char* basename);

#endif  // _VMTWRITER_H_
