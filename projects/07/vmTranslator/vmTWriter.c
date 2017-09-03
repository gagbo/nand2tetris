#include "vmTWriter.h"

void write_to_file(FILE* filestream, const char** command,
                   LabelCounter* p_labelCounter, const char* asm_stub,
                   int asm_stub_number, char* basename) {
    char* asm_stub_copy = strdup(asm_stub);
    const char* sep = " .=";
    /* Keywords to change :
     * BASENAME -> basename
     * I -> asm_stub_number
     * CLASSIC -> LCL or ARG or THIS or THAT or TEMP
     * B -> THIS if asm_sub_number == 0; THAT if asm_stub_number == 1
     */
    // TODO : Use strtok bc it replaces
    char* line = strtok(asm_stub_copy, "\n");
    while (line != NULL) {
        fprintf(stderr, "%s", line);
        char asm_line_buffer[ASM_LINE_BUFFER_SIZE];
        asm_line_buffer[0] = '\0';
        // TODO : Do not use strtok because we won't replace
        char* significant_word = line;
        // Take out the '@' special case
        if (strncmp(line, "@", 1) == 0) {
            strcat(asm_line_buffer, "@");
            line += 1;
        }
        size_t s_word_length = strcspn(line, sep);
        while (s_word_length != 0) {
            if (strncmp(significant_word, "BASENAME", s_word_length) == 0) {
                strcat(asm_line_buffer, basename);
                strcat(asm_line_buffer, " ");
            } else if (strncmp(significant_word, "I", s_word_length) == 0) {
                strcat(asm_line_buffer, command[2]);
                strcat(asm_line_buffer, " ");
            } else if (strncmp(significant_word, "CLASSIC", s_word_length) ==
                       0) {
                if (strcmp(command[1], "local") == 0) {
                    strcat(asm_line_buffer, "LCL ");
                } else if (strcmp(command[1], "argument") == 0) {
                    strcat(asm_line_buffer, "ARG ");
                } else if (strcmp(command[1], "this") == 0) {
                    strcat(asm_line_buffer, "THIS ");
                } else if (strcmp(command[1], "that") == 0) {
                    strcat(asm_line_buffer, "THAT ");
                } else if (strcmp(command[1], "temp") == 0) {
                    strcat(asm_line_buffer, "TEMP ");
                }
            } else if (strncmp(significant_word, "B", s_word_length) == 0) {
                if (asm_stub_number == 0) {
                    strcat(asm_line_buffer, "THIS ");
                } else if (asm_stub_number == 0) {
                    strcat(asm_line_buffer, "THAT ");
                } else {
                    fprintf(stderr, "Number not recognised in pointer command");
                    exit(1);
                }
            } else {
                strncat(asm_line_buffer, significant_word, s_word_length);
                strcat(asm_line_buffer, " ");
            }
            // Advance the significant_word pointer
            significant_word += s_word_length;
            // Write all the separator characters and then skip them
            size_t number_of_sep_to_write = strspn(significant_word, sep);
            strncat(asm_line_buffer, significant_word, number_of_sep_to_write);
            significant_word += number_of_sep_to_write;
            // Find the next significant word to advance the loop
            s_word_length = strcspn(significant_word, sep);
        }
        fputs(asm_line_buffer, filestream);
        fputs("\n", filestream);
        line = strtok(NULL, "\n");
    }
    free(asm_stub_copy);
}

const char* choose_asm_dict_file(const char** command, int command_len) {
    if (command_len == 1) {
        if (strcmp(command[0], "add") == 0) {
            return add_asm;
        } else if (strcmp(command[0], "and") == 0) {
            return and_asm;
        } else if (strcmp(command[0], "eq") == 0) {
            return eq_asm;
        } else if (strcmp(command[0], "gt") == 0) {
            return gt_asm;
        } else if (strcmp(command[0], "lt") == 0) {
            return lt_asm;
        } else if (strcmp(command[0], "neg") == 0) {
            return neg_asm;
        } else if (strcmp(command[0], "not") == 0) {
            return not_asm;
        } else if (strcmp(command[0], "or") == 0) {
            return or_asm;
        } else if (strcmp(command[0], "sub") == 0) {
            return sub_asm;
        }

    } else if (command_len == 3) {
        // Big old string switch
        if (strcmp(command[0], "push") == 0 &&
            strcmp(command[1], "pointer") == 0) {
            return push_pointer_b_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "pointer") == 0) {
            return pop_pointer_b_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "constant") == 0) {
            return push_constant_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "static") == 0) {
            return pop_static_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "static") == 0) {
            return push_static_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "local") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "argument") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "this") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "that") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(command[0], "pop") == 0 &&
                   strcmp(command[1], "temp") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "local") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "argument") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "this") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "that") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(command[0], "push") == 0 &&
                   strcmp(command[1], "temp") == 0) {
            return push_classic_i_asm;
        }
    }
    return NULL;
}
