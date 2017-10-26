/* Copyright 2017 Gerry Agbobada
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
