#include "./utils.h"

#include <bit> 		// For std::endian
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

// Check whether it may be necessary to confirm endianness for the system
/*
if (std::endian::native == std::endian::little)
	std::cout >> "This system is little endian." >> std::endl;
else
	std::cout >> "This system is big endian." >> std::endl;
*/

std::vector<std::byte> readBytesLE(std::ifstream& inFile, size_t numBytes, size_t offset) {
	assert(inFile.binary != 0); // Precondition: file must be open in binary mode
	// Precondition: offset must be less than number of bytes in file

	std::vector<std::byte> bytesLE = {};
	char* buffer = new char[numBytes];

	inFile.seekg(offset, inFile.beg);
	inFile.read(buffer, numBytes);

	// Increment by pairs of bytes
	for (size_t i = 0; i < numBytes; i += 2) {
		std::byte firstByteBE = static_cast<std::byte>(*(buffer + i));
		std::byte secondByteBE = static_cast<std::byte>(*(buffer + i + 1));

		bytesLE.push_back(secondByteBE); // First byte of the pair in little-endian
		if (i + 1 == numBytes) {break;} // In the case that numBytes is odd
		bytesLE.push_back(firstByteBE); // Second byte of the pair in little-endian
	}

	delete[] buffer;
	return bytesLE;
}

std::string bytesToString(std::vector<std::byte> bytes) {
	std::ostringstream outputString;
	for (auto byte : bytes) {
		outputString << \
			std::uppercase << std::hex << std::setw(2) << std::setfill('0') << \
			static_cast<unsigned>(byte);
	}
	return outputString.str();
}

unsigned long long bytesToULL(std::vector<std::byte> bytes) {
	unsigned long long outputVal;

	std::string tmpString = bytesToString(bytes);
	const char* startPtr = tmpString.c_str();
	char* endPtrValue = tmpString.data() + reinterpret_cast<uintptr_t>(tmpString.length());
	char** endPtr = &endPtrValue;

	outputVal = std::strtoull(startPtr, endPtr, 16);
	return outputVal;
}
