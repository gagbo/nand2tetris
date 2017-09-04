#include "vmTParser.h"

int parse_line(const char* line, VMCommand* p_cmd) {
    int wordCount = 0;
    char* nextWord = NULL;
    char* line_copy = strdup(line);

    // Read each token into command, until
    nextWord = strtok(line_copy, " \n\r\t");
    while (nextWord != NULL && wordCount < MAX_COMMAND_WORDS) {
        if (strncmp(nextWord, "//", 2) == 0) {
            break;
        }
        strcpy(p_cmd->command[wordCount], nextWord);
        ++wordCount;
        nextWord = strtok(NULL, " \n\r\t");
    }

    free(line_copy);
    return wordCount;
}
