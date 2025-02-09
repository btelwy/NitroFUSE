# Variable definitions start
SRC_DIR := NitroFUSE
BUILD_DIR := build
WARNINGS := -Wall -Wextra -Werror -pedantic
SANITIZER := -fsanitize=address -fsanitize=leak -fsanitize=undefined
SECURITY := -fhardened
# I'd like to use -fhardened, but that requires GCC 14 and I have GCC 13

COMPILER := g++
STANDARD := -std=c++20
NOASSERTS := -DNODEBUG
FLAGS_COMMON := $(COMPILER) $(STANDARD)

# These can be used by passing MODE={release,sanitizer,debug,coverage} on the command line
# SANITIZER is the default mode unless a different mode is specified
FLAGS_RELEASE := $(FLAGS_COMMON) -O2 -s $(NOASSERTS)
FLAGS_SANITIZER := $(FLAGS_COMMON) -O2 -g $(WARNINGS) $(SANITIZER)
FLAGS_DEBUG := $(FLAGS_COMMON) -Og -ggdb3 -fno-omit-frame-pointer $(WARNINGS)
FLAGS_COVERAGE := $(FLAGS_COMMON) -O2 -g --coverage $(WARNINGS) $(NOASSERTS)

# ----------------------------------
.PHONY: all
.PHONY: init
.PHONY: build

.PHONY: unittest
.PHONY: report
.PHONY: clean
.PHONY: install

# ----------------------------------
all: init build

# Pre-build steps
init:
MODE ?= sanitizer

ifeq ($(MODE),release)
CXX = $(FLAGS_RELEASE)
else ifeq ($(MODE),sanitizer)
CXX = $(FLAGS_SANITIZER)
else ifeq ($(MODE),debug)
CXX = $(FLAGS_DEBUG)
else ifeq ($(MODE),coverage)
CXX = $(FLAGS_COVERAGE)
endif

build: main.o process_rom.o nitrorom.o
	$(CXX) $(foreach file,$^,$(BUILD_DIR)/$(file)) -o $(BUILD_DIR)/nitrofuse
	@echo "Build mode used: $(MODE)"
	@echo ""
	@echo "------------------------"
	@$(BUILD_DIR)/nitrofuse

main.o:
	$(CXX) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

process_rom.o:
	$(CXX) -c $(SRC_DIR)/process_rom.cpp -o $(BUILD_DIR)/process_rom.o

nitrorom.o:
	$(CXX) -c $(SRC_DIR)/nitrorom.cpp -o $(BUILD_DIR)/nitrorom.o

# ---------------------------
# Optional unit test build target
unittest:
	@echo something

# make must first be run with MODE=coverage to enable this coverage report
report:
	gcov $(BUILD_DIR)/main.cpp $(BUILD_DIR)/process_rom.cpp
	lcov --capture --directory $(BUILD_DIR) --build-directory $(BUILD_DIR) --output-file $(BUILD_DIR)/coverage.info
	genhtml $(BUILD_DIR)/coverage.info --output-directory $(BUILD_DIR)/coverage
	rm *.gcov

# Optional install target
install:
	@echo something

# Optional clean target
clean:
	rm -rf $(BUILD_DIR)/*
