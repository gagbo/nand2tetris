#include "vmTParser.h"

int parse_line(const char* line, char** command) {
    int wordCount = 0;
    char* nextWord = NULL;
    char* line_copy = strdup(line);
    for (int i = 0; i < MAX_COMMAND_WORDS; ++i) {
        free(command[i]);
    }

    // Read each token into command, until
    nextWord = strtok(line_copy, " \r\t");
    while (nextWord != NULL && wordCount < MAX_COMMAND_WORDS) {
        if (strncmp(nextWord, "//", 2) == 0) {
            break;
        }
        command[wordCount] = strdup(nextWord);
        ++wordCount;
        nextWord = strtok(NULL, " \r\t");
    }

    free(line_copy);
    return wordCount;
}
