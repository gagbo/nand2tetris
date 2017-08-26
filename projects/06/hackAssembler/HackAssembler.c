#include "HackAssembler.h"

// For the time being, we aim to translate a file stripped of whitespaces, and
// free of symbols. Handling files to get to this point will be done in another
// module

int main(int argc, char** argv) {
    // 1) Open the file or throw error
    char filename[50];
    if (argc > 2) {
        printf("Too many arguments supplied.\n");
        return 1;
    } else if (argc <= 1) {
        printf("One argument expected.\n");
        return 1;
    } else {
        strcpy(filename, argv[1]);
    }

    // Allocate filestream and parse it
    FILE* filestream = NULL;
    HackInstructions list = NULL;
    filestream = fopen(filename, "r");

    // This is where a symbol parser should work to get a symbol-less .asm
    // The translation should make all (LABEL) disappear, and
    // replace them in an intermediate filestream with their values.
    // It should use a map.
    // TODO : implement a hash table for the symbol table
    // TODO : make the symbol translator

    // At this point, filestream is a label-less .asm stream
    // variables can stay and will be replaced
    // filestream is read line by line into char* line
    // Returns the count of read instructions
    uint32_t instructionCount =
        symbolless_stream_to_machine_code(filestream, &list);
    fclose(filestream);
    fprintf(stderr, "Parsing finished, %d instructions total\n",
            instructionCount);
    HI_print_all_instructions(list);
    HI_delete_all_instructions(list);
    return 0;
}
