/**
 * @file		process_rom.h
 * @author		Name <email>
 * @date 		2-2025
 * @version		alpha
 * @copyright
 * This file is part of NitroFUSE, a FUSE implementation for DS ROMs.
 * Copyright (C) 2025 {NAME}
 * @par
 * This program is free/libre software and can be distributed under the terms of the GNU GPLv3.
 * See LICENSE in the project root directory for the full license text.
 */

#ifndef _PROCESS_ROM_H_
#define _PROCESS_ROM_H_ 1

// #include "file_formats/file_formats.h"

// Check about whether it's okay to duplicate includes in each file for readability
#include <fstream>
#include <string>

// State preconditions and postconditions in comments in interfaces

/**
 * @brief
 * Parses a DS ROM.
 * @param rom
 * @p rom is an argument of type @p FILE*
 * @param arg2
 * @p arg2 is another argument
 * @returns retval
 * A return value
 * @throws exception_object
 * Throws an exception
 * @todo
 * Everything
 */
int processRom(const std::string& fileName);
bool verifyIsValidDsRom(std::ifstream& inputFile);

#endif
