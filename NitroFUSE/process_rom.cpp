#include "process_rom.h"

#include <iostream>
#include <iterator>

int processRom(const std::string& fileName) {
	std::ifstream rom(fileName, std::ios::binary);

	if (!verifyIsValidDsRom(rom)) {
		std::cout << "not a valid DS ROM" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool verifyIsValidDsRom(std::ifstream& rom) {
	// implement

	int bufLength = 16;
	char* buf = new char[bufLength];

	rom.seekg(0x15C); // the address of checksum of Nintendo logo, always 0xCF56
	rom.get(buf, bufLength - 1);

	for (int i = 0; i < bufLength; ++i)
		std::cout << std::hex << buf << std::endl;

	return true;
}
