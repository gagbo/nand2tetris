#include "vmTMain.h"

int main(int argc, char **argv) {
    char filename[50];
    char *filename_copy = NULL;
    char *file_label = NULL;
    if (argc > 2) {
        printf("Too many arguments supplied.\n");
        return 1;
    } else if (argc <= 1) {
        printf("One argument expected.\n");
        return 1;
    } else {
        strcpy(filename, argv[1]);
        filename_copy = strdup(filename);
        char *file_basename = basename(filename_copy);
        file_label = strtok(file_basename, ".");
    }

    // Allocate filestream and parse it
    FILE *filestream = NULL;
    LabelCounter LabelCounter;
    LabelCounter.nb_all = 0;
    filestream = fopen(filename, "r");
    if (filestream == NULL) {
        fprintf(stderr, "Could not open %s\n", filename);
        free(filename_copy);
        return 1;
    }

    char line[LINE_BUFFERSIZE];
    char **command = calloc(MAX_COMMAND_WORDS, sizeof(char *));
    while (fgets(line, LINE_BUFFERSIZE - 1, filestream) != NULL) {
        int command_length = parse_line(line, command);
        if (command_length == 0) {
            continue;
        } else {
            // This is where we should call the writing functions
            const char *asm_dict_file =
                choose_asm_dict_file(command, command_length);
            write_to_file(stdout, command, &LabelCounter, asm_dict_file, 0,
                          file_label);
        }
        // Free the memory allocated by parse_line
        // TODO : have alloc and free at the same place
        for (int i = 0; i < command_length; ++i) {
            free(command[i]);
        }
    }

    free(command);
    fclose(filestream);
    free(filename_copy);

    return 0;
}
