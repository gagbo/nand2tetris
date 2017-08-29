#include "vmTWriter.h"

const unsigned char* choose_asm_dict_file(const char** command,
                                          int command_len) {
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
