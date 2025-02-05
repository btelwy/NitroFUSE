# Variable definitions start
COMPILER := g++

WARNINGS := -Wall -Wextra -pedantic
SANITIZERS := -fsanitize=address -fsanitize=leak -fsanitize=undefined
CXXFLAGS_COMMON := -std=c++20 -fPIC
CXXFLAGS := -O2 $(CXXFLAGS_COMMON)
CXXFLAGS_DEBUG := -Werror -Og -ggdb -fno-omit-frame-pointer -fprofile-arcs -ftest-coverage \
	$(SANITIZERS) $(WARNINGS) $(CXXFLAGS_COMMON)

CXX := $(COMPILER) $(CXXFLAGS_COMMON) $(CXXFLAGS) $(WARNINGS)

SRC_DIR := NitroFUSE
BUILD_DIR := build

# ----------------------------------
# Targets start

# Default (release) build target
.PHONY: all
all: main.o
	$(CXX) main.o process_rom.o -o $(BUILD_DIR)/nitrofuse

main.o: process_rom.o
	$(CXX) -c main.cpp -o main.o

process_rom.o: clean
	$(CXX) -c process_rom.cpp -o process_rom.o
# ---------------------------

# Optional debug build target
.PHONY: debug
debug:
	@echo something

# Optional tests target
.PHONY: tests
tests:
	@echo something

# Optional coverage target
.PHONY: coverage
coverage:
	@echo something

# Optional clean target
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

# Optional install target
.PHONY: install
install:
	@echo something
