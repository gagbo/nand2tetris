#include "vmTMain.h"

int main(int argc, char **argv) {
    char filename[50];
    char output_filename[50];
    char *filename_copy = NULL;
    char *filename_copy2 = NULL;
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
        filename_copy2 = strdup(filename);
        char *file_basename = basename(filename_copy);
        file_label = strtok(file_basename, ".");
        // strtok modified definitely file_basename
        // so we can just use file_label or file_basename indifferently
        char *file_dirname = dirname(filename_copy2);
        strcpy(output_filename, file_dirname);
        strcat(output_filename, "/");
        strcat(output_filename, file_label);
        strcat(output_filename, ".asm");
    }

    // Allocate filestream and parse it
    FILE *filestream = NULL;
    FILE *outputstream = NULL;
    LabelCounter LabelCounter;
    LabelCounter.nb_all = 0;
    filestream = fopen(filename, "r");
    outputstream = fopen(output_filename, "w");
    if (filestream == NULL) {
        fprintf(stderr, "Could not open %s\n", filename);
        free(filename_copy);
        free(filename_copy2);
        return 1;
    }

    // Allocation of resources for the translation
    char line[LINE_BUFFERSIZE];
    char **command = calloc(MAX_COMMAND_WORDS, sizeof(char *));
    // .vm file parsing loop
    while (fgets(line, LINE_BUFFERSIZE - 1, filestream) != NULL) {
        int command_length = parse_line(line, command);
        // Skip the line if it is a comment
        if (command_length == 0) {
            continue;
        } else {
            // This is where we should call the writing functions
            const char *asm_dict_file =
                choose_asm_dict_file(command, command_length);
            write_to_file(outputstream, command, &LabelCounter, asm_dict_file,
                          file_label);
        }
        // Free the memory allocated by parse_line
        // TODO : have alloc and free at the same place
        for (int i = 0; i < command_length; ++i) {
            free(command[i]);
        }
    }

    // Cleanup
    free(command);
    fclose(filestream);
    fclose(outputstream);
    free(filename_copy);
    free(filename_copy2);

    return 0;
}
