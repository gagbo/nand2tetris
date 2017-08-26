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
    HackSymbolTable table;
    ST_initialise(&table);
    filestream = fopen(filename, "r");

    parser_labels_pass(filestream, &table);

    // At this point, Symbol table is filled, and labels will be
    // ignored.
    // Variables can stay and will be replaced
    // Returns the count of read instructions
    filestream = freopen(NULL, "r", filestream);
    uint32_t instructionCount =
        symbolless_stream_to_machine_code(filestream, &list, &table);
    fclose(filestream);
    fprintf(stderr, "Parsing finished, %d instructions total\n",
            instructionCount);
    HI_print_all_instructions(&list);
    HI_delete_all_instructions(&list);
    ST_delete_all_entries(&table);
    return 0;
}
