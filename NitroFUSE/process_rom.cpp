#include "process_rom.h"

#include <bitset>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>

int processRom(const std::string& fileName) {
	std::ifstream rom(fileName, std::ios::binary);
	if (rom.fail()) {
		std::cout << "Error: could not open file " << fileName << "." << std::endl;
		return EXIT_FAILURE;
	}

	rom.seekg(std::ios::end);
	[[maybe_unused]] double fileSize = rom.tellg();
	rom.seekg(std::ios::beg);

	if (!verifyIsDsRom(rom)) {
		std::cout << "Error: " << fileName << " is not a valid DS ROM." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool verifyIsDsRom(std::ifstream& rom) {
	static const size_t NINTENDO_LOGO_CHECKSUM_OFFSET = 0x15C;
	[[maybe_unused]] static const size_t NINTENDO_LOGO_CHECKSUM_VALUE = 0xCF56;
	static const size_t NINTENDO_LOGO_CHECKSUM_LENGTH = 2;

	char* checksum = new char[NINTENDO_LOGO_CHECKSUM_LENGTH];

	rom.seekg(NINTENDO_LOGO_CHECKSUM_OFFSET, std::ifstream::beg);
	rom.get(checksum, NINTENDO_LOGO_CHECKSUM_LENGTH);
	std::cout << std::hex << checksum << std::endl;

	//mmap()

	delete[] checksum;
	return true;
}
