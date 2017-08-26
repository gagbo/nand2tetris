#include "HackParser.h"

uint32_t symbolless_stream_to_machine_code(FILE* filestream,
                                           HackInstructions* list) {
    char line[LINE_BUFFERSIZE];
    uint32_t instructionCount = 0;
    /* uint16_t variableAddress = 16; */
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
            HackInstruction* Ainstruction = malloc(sizeof(HackInstruction));
            char* label = strtok(strippedInstruction, "@");
            // If the first char of the label is a digit, then we assume it's an
            // address
            if (isdigit(label[0])) {
                set_AInstruction(Ainstruction, strtol(label, NULL, 10));
            } else {  // else we have to convert a label
                // look the label in hash table
                // If it exists, set_AInstruction(Ainstr, symbol_table(label));
                // If it doesn't, add to the symbol table with label->
                // variableAddress and increment variableAddress
            }
            Ainstruction->lineNumber = instructionCount;
            HI_push_back(list, Ainstruction);
            /* fprintf(stderr, "%d ", instructionCount); */
            ++instructionCount;
            /* fprintf(stderr, "State of the Machine Code : \n"); */
            /* HI_print_all_instructions(*list); */

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
            HackInstruction* Cinstruction = malloc(sizeof(HackInstruction));
            set_CInstruction(Cinstruction, dest, comp, jump);
            Cinstruction->lineNumber = instructionCount;
            HI_push_back(list, Cinstruction);
            /* fprintf(stderr, "%d ", instructionCount); */
            ++instructionCount;
            /* fprintf(stderr, "State of the Machine Code : \n"); */
            /* HI_print_all_instructions(*list); */
        }
    }
    return instructionCount;
}
