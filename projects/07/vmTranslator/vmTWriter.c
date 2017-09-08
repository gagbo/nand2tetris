#include "vmTWriter.h"

void LC_init(LabelCounter* p_lc) {
    p_lc->nb_all = 0;
    p_lc->nb_return = 0;
}

void LC_reset_return_counter(LabelCounter* p_lc) { p_lc->nb_return = 0; }

void write_to_file(FILE* filestream, const VMCommand* p_cmd,
                   LabelCounter* p_labelCounter, const char* asm_stub,
                   char* basename, char* staticName) {
    char* asm_stub_copy = strdup(asm_stub);
    const char* sep = " .=@()$";
    /* Keywords to change :
     * BASENAME -> basename
     * I -> asm_stub_number
     * J -> Label Counter
     * CLASSIC -> LCL or ARG or THIS or THAT or TEMP
     * B -> THIS if asm_sub_number == 0; THAT if asm_stub_number == 1
     */
    // TODO : Use strtok bc it replaces
    char* line = strtok(asm_stub_copy, "\r\n");
    while (line != NULL) {
        char asm_line_buffer[ASM_LINE_BUFFER_SIZE];
        asm_line_buffer[0] = '\0';
        // TODO : Do not use strtok because we won't replace
        char* significant_word = line;
        // Take out the '@' special case and the '(' one
        if (strncmp(line, "@", 1) == 0) {
            strcat(asm_line_buffer, "@");
            line += 1;
            significant_word += 1;
        } else if (strncmp(line, "(", 1) == 0) {
            strcat(asm_line_buffer, "(");
            line += 1;
            significant_word += 1;
        }
        size_t s_word_length = strcspn(line, sep);
        while (significant_word && *significant_word) {
            if (strncmp(significant_word, "BASENAME", s_word_length) == 0) {
                strcat(asm_line_buffer, basename);
            } else if (strncmp(significant_word, "STATICNAME", s_word_length) ==
                       0) {
                strcat(asm_line_buffer, staticName);
            } else if (strncmp(significant_word, "CALLEENAME", s_word_length) ==
                       0) {
                strcat(asm_line_buffer, p_cmd->command[1]);
            } else if (strncmp(significant_word, "LABEL", s_word_length) == 0) {
                strcat(asm_line_buffer, p_cmd->command[1]);
            } else if (strncmp(significant_word, "FUNCTIONNAME",
                               s_word_length) == 0) {
                strcat(asm_line_buffer, p_cmd->functionName);
            } else if (strncmp(significant_word, "I", s_word_length) == 0) {
                strcat(asm_line_buffer, p_cmd->command[2]);
            } else if (strncmp(significant_word, "J", s_word_length) == 0) {
                char nb_all_string[15];
                sprintf(nb_all_string, "%d", p_labelCounter->nb_all);
                strcat(asm_line_buffer, nb_all_string);
            } else if (strncmp(significant_word, "CLASSIC", s_word_length) ==
                       0) {
                if (strcmp(p_cmd->command[1], "local") == 0) {
                    strcat(asm_line_buffer, "LCL");
                } else if (strcmp(p_cmd->command[1], "argument") == 0) {
                    strcat(asm_line_buffer, "ARG");
                } else if (strcmp(p_cmd->command[1], "this") == 0) {
                    strcat(asm_line_buffer, "THIS");
                } else if (strcmp(p_cmd->command[1], "that") == 0) {
                    strcat(asm_line_buffer, "THAT");
                } else if (strcmp(p_cmd->command[1], "temp") == 0) {
                    strcat(asm_line_buffer, "5");
                }
            } else if (strncmp(significant_word, "K", s_word_length) == 0) {
                if (atoi(p_cmd->command[2]) == 0) {
                    strcat(asm_line_buffer, "THIS");
                } else if (atoi(p_cmd->command[2]) == 1) {
                    strcat(asm_line_buffer, "THAT");
                } else {
                    fprintf(stderr, "Number not recognised in pointer command");
                    exit(1);
                }
            } else if (strncmp(significant_word, "RET_ID", s_word_length) ==
                       0) {
                char nb_ret_string[15];
                sprintf(nb_ret_string, "%d", p_labelCounter->nb_return);
                strcat(asm_line_buffer, nb_ret_string);
            } else {
                strncat(asm_line_buffer, significant_word, s_word_length);
                /* strcat(asm_line_buffer, " "); */
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

    if (asm_stub == return_asm) {
        LC_reset_return_counter(p_labelCounter);
    } else if (asm_stub == call_asm) {
        p_labelCounter->nb_return++;
    }
    p_labelCounter->nb_all++;
    free(asm_stub_copy);
}

const char* choose_asm_dict_file(VMCommand* p_cmd, int command_len) {
    if (command_len == 1) {
        if (strcmp(p_cmd->command[0], "add") == 0) {
            return add_asm;
        } else if (strcmp(p_cmd->command[0], "and") == 0) {
            return and_asm;
        } else if (strcmp(p_cmd->command[0], "eq") == 0) {
            return eq_asm;
        } else if (strcmp(p_cmd->command[0], "gt") == 0) {
            return gt_asm;
        } else if (strcmp(p_cmd->command[0], "lt") == 0) {
            return lt_asm;
        } else if (strcmp(p_cmd->command[0], "neg") == 0) {
            return neg_asm;
        } else if (strcmp(p_cmd->command[0], "not") == 0) {
            return not_asm;
        } else if (strcmp(p_cmd->command[0], "or") == 0) {
            return or_asm;
        } else if (strcmp(p_cmd->command[0], "sub") == 0) {
            return sub_asm;
        } else if (strcmp(p_cmd->command[0], "return") == 0) {
            return return_asm;
        }

    } else if (command_len == 3) {
        // Big old string switch
        if (strcmp(p_cmd->command[0], "push") == 0 &&
            strcmp(p_cmd->command[1], "pointer") == 0) {
            return push_pointer_b_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "pointer") == 0) {
            return pop_pointer_b_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "constant") == 0) {
            return push_constant_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "static") == 0) {
            return pop_static_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "static") == 0) {
            return push_static_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "local") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "argument") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "this") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "that") == 0) {
            return pop_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "pop") == 0 &&
                   strcmp(p_cmd->command[1], "temp") == 0) {
            return pop_temp_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "local") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "argument") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "this") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "that") == 0) {
            return push_classic_i_asm;
        } else if (strcmp(p_cmd->command[0], "push") == 0 &&
                   strcmp(p_cmd->command[1], "temp") == 0) {
            return push_temp_i_asm;
        } else if (strcmp(p_cmd->command[0], "function") == 0) {
            VMC_set_function_name(p_cmd, p_cmd->command[1]);
            return function_asm;
        } else if (strcmp(p_cmd->command[0], "call") == 0) {
            return call_asm;
        }
    } else if (command_len == 2) {
        if (strcmp(p_cmd->command[0], "label") == 0) {
            return label_asm;
        } else if (strcmp(p_cmd->command[0], "goto") == 0) {
            return goto_asm;
        } else if (strcmp(p_cmd->command[0], "if-goto") == 0) {
            return if_goto_asm;
        }
    }
    return NULL;
}
