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
    char line[256];
    uint32_t instructionCount = 0;
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
    // TODO : put in a function
    // Returns the count of read instructions
    // uint32_t symbolless_stream_to_machine_code(FILE * filestream,
    //                                            Instructions list)
    while (fgets(line, 255, filestream) != NULL) {
        char* nextWord;
        char strippedInstruction[20];
        strippedInstruction[0] = '\0';
        // This loop uses strtok to remove all whitespaces in line.
        // Also, if a bracket or a comment symbol is found, we skip to
        // next line
        nextWord = strtok(line, " \r\n\t");
        while (nextWord != NULL) {
            // Stop reading the line if there is one of those symbols
            if (strncmp(nextWord, "//", 2) == 0) {
                break;
            }
            // Otherwise, add the new meaningful symbol, and go the next one
            strcat(strippedInstruction, nextWord);
            nextWord = strtok(NULL, " ");
        }
        // This is needed to skip comment lines or open/close brackets
        if (strlen(strippedInstruction) == 0) {
            continue;
        }
        // See if line[0] is @
        // a) if it is, then Ainstruction
        if (strncmp(strippedInstruction, "@", 1) == 0) {
            // If the value after the @ is not numeric, then we
            // should look it up in the symbol table
            // if found we replace it,
            // if not, we make the 16++ foo
            HackInstruction Ainstruction;
            set_AInstruction(&Ainstruction,
                             strtol(strippedInstruction + 1, NULL, 10));
            Ainstruction.lineNumber = instructionCount;
            /* fprintf(stderr, "%d ", instructionCount); */
            ++instructionCount;
            printInstruction(&Ainstruction);
        } else {  // b) else, parse for C instruction
            // TODO : make the string uppercase
            char* dest = NULL;
            char* comp = NULL;
            // Check if destination is specified before cutting
            // the C-instruction string
            if (strchr(strippedInstruction, '=') != NULL) {
                dest = strtok(strippedInstruction, "=");
                comp = strtok(NULL, ";\r\n");
            } else {
                comp = strtok(strippedInstruction, ";\r\n");
            }
            char* jump = strtok(NULL, "\r\n");
            HackInstruction Cinstruction;
            set_CInstruction(&Cinstruction, dest, comp, jump);
            Cinstruction.lineNumber = instructionCount;
            /* fprintf(stderr, "%d ", instructionCount); */
            ++instructionCount;
            printInstruction(&Cinstruction);
        }
    }
    return 0;
}
