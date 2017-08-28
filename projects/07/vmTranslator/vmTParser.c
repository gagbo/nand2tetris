#include "vmTParser.h"

int parse_line(char* line, char** command) {
    int wordCount = 0;
    char* nextWord = NULL;
    for (int i = 0; i < MAX_COMMAND_WORDS; ++i) {
        free(command[i]);
    }

    // Read each token into command, until
    nextWord = strtok(line, " \r\t");
    while (nextWord != NULL && wordCount < MAX_COMMAND_WORDS) {
        if (strncmp(nextWord, "//", 2) == 0) {
            break;
        }
        command[wordCount] = strdup(nextWord);
        ++wordCount;
        nextWord = strtok(NULL, " \r\t");
    }

    return wordCount;
}
