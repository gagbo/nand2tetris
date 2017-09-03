#include "vmTWriter.h"

void write_to_file(FILE* filestream, const char** command,
                   LabelCounter* p_labelCounter, const char* asm_stub,
                   int asm_stub_number, char* basename) {
    char* asm_stub_copy = strdup(asm_stub);
    /* Keywords to change :
     * BASENAME -> basename
     * I -> asm_stub_number
     * CLASSIC -> LCL or ARG or THIS or THAT or TEMP
     * B -> THIS if asm_sub_number == 0; THAT if asm_stub_number == 1
     */
    char* line = strtok(asm_stub_copy, "\n");
    while (line != NULL) {
        char asm_line_buffer[ASM_LINE_BUFFER_SIZE];
        asm_line_buffer[0] = '\0';
        char* significant_word = strtok(line, " \n\r\t.=@;");
        while (significant_word != NULL) {
            if (strcmp(significant_word, "BASENAME") == 0) {
                strcat(asm_line_buffer, basename);
            } else if (strcmp(significant_word, "I") == 0) {
                strcat(asm_line_buffer, command[2]);
            } else if (strcmp(significant_word, "CLASSIC") == 0) {
                if (strcmp(command[1], "local") == 0) {
                    strcat(asm_line_buffer, "LCL");
                } else if (strcmp(command[1], "argument") == 0) {
                    strcat(asm_line_buffer, "ARG");
                } else if (strcmp(command[1], "this") == 0) {
                    strcat(asm_line_buffer, "THIS");
                } else if (strcmp(command[1], "that") == 0) {
                    strcat(asm_line_buffer, "THAT");
                } else if (strcmp(command[1], "temp") == 0) {
                    strcat(asm_line_buffer, "TEMP");
                }
            } else if (strcmp(significant_word, "B") == 0) {
                if (asm_stub_number == 0) {
                    strcat(asm_line_buffer, "THIS");
                } else if (asm_stub_number == 0) {
                    strcat(asm_line_buffer, "THAT");
                } else {
                    fprintf(stderr, "Number not recognised in pointer command");
                    exit(1);
                }
            } else {
                strcat(asm_line_buffer, significant_word);
            }
            significant_word = strtok(line, " \n\r\t.=@;");
        }
        fputs(asm_line_buffer, filestream);
        line = strtok(asm_stub_copy, "\n");
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
