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
#ifndef _VMTPARSER_H_
#define _VMTPARSER_H_
#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__
#include <stdlib.h>
#include <string.h>
#include "vmTTools.h"

/* Parse the words on the line, and put results in command array
 * returns the number of words read, so if it returns 0 we can
 * go the the next line in main
 * command has to be malloc'd to be size MAX_COMMAND_WORDS
 */
int parse_line(const char* line, VMCommand* p_cmd);

#endif  // _VMTPARSER_H_
