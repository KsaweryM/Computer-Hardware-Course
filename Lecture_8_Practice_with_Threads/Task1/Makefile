# Compiles every .cpp file of this folder into build/.
#   make         compile
#   make run     compile and run
#   make clear   remove build/
CXX := g++
CXXFLAGS := -std=c++20 -O0 -Wall -pthread
BUILD_DIR := build
PROGRAMS := $(patsubst %.cpp,$(BUILD_DIR)/%,$(wildcard *.cpp))
# the one program of this task, for make run
PROGRAM := $(BUILD_DIR)/$(basename $(wildcard *.cpp))

.PHONY: make run clear

make: $(PROGRAMS)

$(BUILD_DIR)/%: %.cpp $(wildcard *.h)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clear:
	rm -rf $(BUILD_DIR)
