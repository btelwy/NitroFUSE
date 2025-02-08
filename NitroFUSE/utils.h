/**
 * @file		utils.h
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

#ifndef _NITRO_UTILS_H_
#define _NITRO_UTILS_H_ 1

#include <cstddef>
#include <fstream>
#include <vector>

// Precondition: file must be open in binary mode
// Precondition: offset must be less than the number of bytes in inFile
std::vector<std::byte> readBytesLE(std::ifstream& inFile, size_t numBytes, size_t offset);

std::string bytesToString(std::vector<std::byte> bytes);
unsigned long long bytesToULL(std::vector<std::byte> bytes);

#endif
