/**
 * @file		nitronode.h
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

#ifndef _NITRONODE_H_
#define _NITRONODE_H_ 1

// #include "file_formats/file_formats.h"

#include <string>
#include <vector>


/**
 * @class
 * @brief
 * Represents a file within the NitroFS tree structure to be passed to the FUSE API.
 * @details
 * "File" is used in the Unix sense, where directories are files too.
 * This class does not contain detailed file metadata, since libfuse handles that instead.
 */

class NitroNode {
	public:
		const std::string name;
		const size_t offsetInFAT;
		const size_t numBytes;

		std::vector<NitroNode*>* subdirVec;
		NitroNode* parentDir;

		const bool thisIsDir;

		NitroNode* addToSubdir(const std::string _name, const size_t _offsetInFAT, const size_t _numBytes, const bool _thisIsDir) {
			if (!thisIsDir) { return nullptr; }

			NitroNode* node = new NitroNode(_name, _offsetInFAT, _numBytes, _thisIsDir);
			if (_offsetInFAT != 0) { node->parentDir = this; } // The root node's parentDir stays as nullptr
			return node;
		}

		NitroNode(const std::string _name, const size_t _offsetInFAT, const size_t _numBytes, const bool _thisIsDir) :
			name(_name),
			offsetInFAT(_offsetInFAT),
			numBytes(_numBytes),

			subdirVec(new std::vector<NitroNode*>),
			parentDir(nullptr),

			thisIsDir(_thisIsDir) {}

		// Calling destructor from the root node will recrusively destroy the entire tree
		~NitroNode() {
			if (thisIsDir) { delete subdirVec; }
		}
};

#endif
