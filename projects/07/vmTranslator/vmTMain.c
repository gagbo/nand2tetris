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
    LC_init(&LabelCounter);
    VMCommand cmd;
    VMC_init(&cmd);

    // Allocation of resources for the translation
    char line[LINE_BUFFERSIZE];

    // .vm file parsing loop
    for (int i = 0; i < ioFiles.fileCount; i++) {
        IOF_set_basename(&ioFiles, ioFiles.input_filenames[i]);
        while (fgets(line, LINE_BUFFERSIZE - 1, ioFiles.input[i]) != NULL) {
            int command_length = parse_line(line, &cmd);
            // Skip the line if it is a comment
            if (command_length == 0) {
                continue;
            } else {
                // This is where we should call the writing functions
                const char *asm_dict_file =
                    choose_asm_dict_file(&cmd, command_length);
                write_to_file(ioFiles.output, &cmd, &LabelCounter,
                              asm_dict_file, ioFiles.basename);
            }
        }
    }

    // Cleanup
    IOF_clear(&ioFiles);
    VMC_clear(&cmd);

    return 0;
}
