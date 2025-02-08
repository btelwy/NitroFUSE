#include "./process_rom.h"
#include "./utils.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int processRom(const std::string& fileName) {
	std::ifstream rom(fileName, std::ios::binary);
	if (rom.fail()) {
		std::cout << "Error: could not open file '" << fileName << "'." << std::endl;
		return EXIT_FAILURE;
	}

	rom.seekg(rom.end);
	// double fileSize = rom.tellg();
	rom.seekg(rom.beg);

	if (!verifyIsDsRom(rom)) {
		std::cout << "Error: '" << fileName << "' is not a valid DS ROM." << std::endl;
		return EXIT_FAILURE;
	}

	// Fixme: implement next steps here

	return EXIT_SUCCESS;
}

bool verifyIsDsRom(std::ifstream& rom) {
	// Details of the Nintendo logo CRC-16 checksum used to check the file is a DS ROM
	const size_t CHECKSUM_OFFSET_BYTES = 0x15C; 				// Offset in bytes from beginning of ROM
	const uint16_t CHECKSUM_VALUE_LE = 0xCF56; 		 			// Value of checksum in little-endian format
	const size_t CHECKSUM_SIZE = sizeof(CHECKSUM_VALUE_LE);		// 2 bytes

	std::vector<std::byte> checksumBytesLE = readBytesLE(rom, CHECKSUM_SIZE, CHECKSUM_OFFSET_BYTES);
	if (bytesToULL(checksumBytesLE) != CHECKSUM_VALUE_LE) {
		return false;
	}
	return true;
}
