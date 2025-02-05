/**
 * @file		file_formats.h
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

#ifndef _FILE_FORMATS_H_
#define _FILE_FORMATS_H_ 1

#include "../compression_types/compression_types.h"

#include <fstream>


enum fileFormats {
	FAT = 0, //think about whether some of these are actually files or just ROM metadata
	BANNER = 1,
	SDAT = 2,

	UNKNOWN
};

/**
 * @class
 * @brief
 * Does stuff
 */
class fileParser {
	public:
		// What information needs to be returned from any file?
		int detectFileFormat(std::ifstream);

	private:
		int hello;
};

#endif
