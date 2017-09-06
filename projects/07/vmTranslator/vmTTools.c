#include "vmTTools.h"

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

void VMC_init(VMCommand *p_vmc) {
    p_vmc->command = calloc(MAX_COMMAND_WORDS, sizeof(char *));
    for (int i = 0; i < MAX_COMMAND_WORDS; ++i) {
        p_vmc->command[i] = calloc(MAX_COMMAND_WORD_LENGTH, sizeof(char *));
    }

    p_vmc->functionName = NULL;
}

void VMC_clear(VMCommand *p_vmc) {
    for (int i = 0; i < MAX_COMMAND_WORDS; ++i) {
        free(p_vmc->command[i]);
    }
    free(p_vmc->command);
    free(p_vmc->functionName);
}

void VMC_set_function_name(VMCommand *p_vmc, char *newFunctionName) {
    p_vmc->functionName = strdup(newFunctionName);
}
