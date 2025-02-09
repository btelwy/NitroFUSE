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

#include <fstream>
#include <string>


/**
 * @brief
 * Processes and extracts necessary data from a DS ROM.
 * @param fileName
 * @p const @p std::string&
 * @returns retval
 * A return value of type @p int
 * @throws exception_object
 * Throws an exception
 * @todo
 * Everything
 */
int processRom(const std::string& fileName);

/**
 * @brief
 * Verifies that the input file is a DS ROM.
 * @details
 * It is not a robust check; it only looks for the Nintendo logo CRC-16 checksum,
 * which is a constant value of 0xCF56 at constant offset from start 0x15C.
 * @param inFile @p std::fstream&
 * @returns @p true if @p inputFile is a DS ROM
 * @throws exception_object
 * Throws an exception
 */
bool verifyIsDsRom(std::fstream& inFile);


#endif
