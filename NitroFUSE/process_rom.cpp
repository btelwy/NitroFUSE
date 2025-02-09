#include "./nitrorom.h"
#include "./process_rom.h"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

int processRom(const std::string& fileName) {
	NitroROM rom(fileName);

	if (!verifyIsDsRom(rom.getFile())) {
		std::cout << "Error: '" << fileName << "' is not a valid DS ROM." << std::endl;
		return EXIT_FAILURE;
	}

	// Fixme: implement next steps here

	return EXIT_SUCCESS;
}

bool verifyIsDsRom(std::fstream& inFile) {
	// Details of the Nintendo logo CRC-16 checksum used to check the file is a DS ROM
	const size_t CHECKSUM_OFFSET = 0x15C;
	const std::string CHECKSUM_VALUE_LE = "CF56";
	const size_t CHECKSUM_SIZE = 2;

	std::vector<std::byte> checksumBytesLE = readBytesLE(inFile, CHECKSUM_SIZE, CHECKSUM_OFFSET, std::ios::beg);
	if (bytesToString(checksumBytesLE) != CHECKSUM_VALUE_LE) {
		return false;
	}
	return true;
}
