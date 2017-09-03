#include "vmTMain.h"

int main(int argc, char **argv) {
    IOFiles ioFiles;
    IOF_init(&ioFiles);
    if (argc > 2) {
        printf("Too many arguments supplied.\n");
        return 1;
    } else if (argc <= 1) {
        printf("One argument expected.\n");
        return 1;
    } else {
        ioFiles = open_filestreams(argv[1]);
        if (!IOF_check(&ioFiles)) {
            fprintf(stderr, "Problem in IOFiles");
            return 1;
        }
    }

    // Allocate filestream and parse it
    LabelCounter LabelCounter;
    LabelCounter.nb_all = 0;

    // Allocation of resources for the translation
    char line[LINE_BUFFERSIZE];
    // TODO : create a VmCommand struct that contains the 3
    // char[MAX_COMMAND_WORD_LENGTH] arrays and a char** to give access to each
    // array through VmCommand.word[i] parse_line and choose_asm_dict_file and
    // write_to_file will need to be modified
    char **command = calloc(MAX_COMMAND_WORDS, sizeof(char *));
    // .vm file parsing loop
    while (fgets(line, LINE_BUFFERSIZE - 1, ioFiles.input) != NULL) {
        int command_length = parse_line(line, command);
        // Skip the line if it is a comment
        if (command_length == 0) {
            continue;
        } else {
            // This is where we should call the writing functions
            const char *asm_dict_file =
                choose_asm_dict_file((const char **)command, command_length);
            write_to_file(ioFiles.output, (const char **)command, &LabelCounter,
                          asm_dict_file, ioFiles.basename);
        }
        // Free the memory allocated by parse_line
        // TODO : have alloc and free at the same place
        for (int i = 0; i < command_length; ++i) {
            free(command[i]);
        }
    }

    // Cleanup
    free(command);
    IOF_clear(&ioFiles);

    return 0;
}

IOFiles open_filestreams(const char *filename) {
    IOFiles ioFiles;
    IOF_init(&ioFiles);
    char *filename_copy = NULL;
    char *filename_copy2 = NULL;
    char output_filename[50];
    output_filename[0] = '\0';
    filename_copy = strdup(filename);
    filename_copy2 = strdup(filename);
    char *file_basename = basename(filename_copy);
    ioFiles.basename = strdup(strtok(file_basename, "."));
    // strtok modified definitely file_basename
    // so we can just use file_label or file_basename indifferently
    char *file_dirname = dirname(filename_copy2);
    strcat(output_filename, file_dirname);
    strcat(output_filename, "/");
    strcat(output_filename, ioFiles.basename);
    strcat(output_filename, ".asm");

    // Allocate filestream and parse it
    ioFiles.input = fopen(filename, "r");
    ioFiles.output = fopen(output_filename, "w");

    free(filename_copy);
    free(filename_copy2);
    return ioFiles;
}

void IOF_clear(IOFiles *p_ioFiles) {
    free(p_ioFiles->basename);
    fclose(p_ioFiles->output);
    fclose(p_ioFiles->input);
}

void IOF_init(IOFiles *p_ioFiles) {
    p_ioFiles->basename = NULL;
    p_ioFiles->output = NULL;
    p_ioFiles->input = NULL;
}

bool IOF_check(IOFiles *p_ioFiles) {
    if (p_ioFiles->basename == NULL) {
        return false;
    } else if (p_ioFiles->output == NULL) {
        return false;
    } else if (p_ioFiles->input == NULL) {
        return false;
    }
    return true;
}
