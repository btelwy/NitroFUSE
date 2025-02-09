#include "./nitrorom.h"

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>


std::vector<std::byte> readBytesLE(std::fstream& inFile, size_t numBytes, size_t startOffset, std::ios::seekdir seekdir) {
	std::vector<std::byte> bytesLE = {};
	char* buffer = new char[numBytes];

	inFile.seekg(startOffset, seekdir);
	inFile.read(buffer, numBytes);

	// Iterate through file by pairs of bytes
	for (size_t i = 0; i < numBytes; i += 2) {
		std::byte firstByte = static_cast<std::byte>(*(buffer + i));
		std::byte secondByte = static_cast<std::byte>(*(buffer + i + 1));

		bytesLE.push_back(secondByte);		// First byte of the pair in little-endian
		if (i + 1 == numBytes) { break; } 		// The case that numBytes is odd
		bytesLE.push_back(firstByte); 		// Second byte of the pair in little-endian
	}

	delete[] buffer;
	return bytesLE;
}

std::string bytesToString(const std::vector<std::byte>& byteVec) {
	std::ostringstream out;
	for (auto byte : byteVec) {
		out << \
		std::uppercase << \
		std::hex << \
		std::setw(2) << \
		std::setfill('0') << \
		static_cast<unsigned int>(byte);
	}
	return out.str();
}

bool printBytesLE(std::fstream& inFile, size_t numBytes, size_t startOffset, std::ios::seekdir seekdir) {
	std::vector<std::byte> bytes = readBytesLE(inFile, numBytes, startOffset, seekdir);
	std::cout << bytesToString(bytes) << std::endl;

	inFile.seekg(startOffset, seekdir); // Return get-pointer to where it was before this function call
	return (inFile.failbit == 4);
}
