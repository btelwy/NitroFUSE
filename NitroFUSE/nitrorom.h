/**
 * @file		nitrorom.h
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

#ifndef _NITROROM_H_
#define _NITROROM_H_ 1

//#include "./nitrofs.h"

#include <fstream>
#include <string>
#include <vector>


/**
 * @class
 * @brief
 *
 */
class NitroROM {
	private:
		std::fstream romFile;

	public:
		const std::string fileName;
		const size_t bytesInRom;
		//NitroFS fs;

		// There used to be a "isLittleEndianSystem" check, but BE architectures are pretty rare

		// Returns a reference to the ROM file of type std::fstream.
		std::fstream& getFile() {
			return romFile;
		}

		// Fixme: these error checks seem to not be correct
		bool fileEof() const {
			return (romFile.eofbit == 2); // eofbit is hardcoded to 2
		}
		bool fileFailed() const {
			return (romFile.failbit == 4); // failbit is hardcoded to 4
		}

		bool seekg(size_t offset, std::ios::seekdir seekdir) {
			romFile.seekg(offset, seekdir);
			return fileFailed();
		}
		std::streampos tellg() {
			return romFile.tellg();
		}
		bool seekp(size_t offset, std::ios::seekdir seekdir) {
			romFile.seekp(offset, seekdir);
			return fileFailed();
		}
		std::streampos tellp() {
			return romFile.tellp();
		}

		explicit NitroROM(const std::string fileNameParam) :
			romFile(fileNameParam, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate),
			fileName(fileNameParam),
			bytesInRom(romFile.tellg())
		{
			romFile.seekg(std::ios::beg); // Undo the effect of std::ios::ate
			romFile.seekp(std::ios::beg);

			//if (fileFailed()) { abort(); }
		};
		~NitroROM() {
			romFile.close();
		};
};

// Reads bytes from a file into a byte vector, following little-endian order.
std::vector<std::byte> readBytesLE(std::fstream& inFile, size_t numBytes, size_t startOffset, std::ios::seekdir seekdir);
// Creates a string with a hex representation of the bytes in a byte vector.
std::string bytesToString(const std::vector<std::byte>& byteVec);

// Combines readBytesLE() and bytesToString() without incrementing the get-pointer.
// Returns a bool indicating health state of file.  Mostly for diagnostic use.
bool printBytesLE(std::fstream& inFile, size_t numBytes, size_t startOffset, std::ios::seekdir seekdir);

#endif
