#include "vmTWriter.h"

void choose_asm_dict_file(char* filename, const char** command, int wordCount) {
    if (wordCount == 1) {
        strcat(filename, command[0]);
        strcat(filename, ".asm");
    } else if (wordCount == 3) {
        // First part of filename :
        // For the time being, only push or pop
        if (strcmp(command[0], "push") == 0) {
            strcat(filename, "push_");
        } else if (strcmp(command[0], "pop") == 0) {
            strcat(filename, "pop_");
        }

        // Second part of filename :
        // pointer, constant, static or classic
        if (strcmp(command[1], "pointer") == 0) {
            strcat(filename, "pointer_b.asm");
        } else if (strcmp(command[1], "constant") == 0) {
            strcat(filename, "constant_i.asm");
        } else if (strcmp(command[1], "static") == 0) {
            strcat(filename, "static_i.asm");
        } else {
            strcat(filename, "classic_i.asm");
        }
    }
}
