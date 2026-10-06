# Compiles every .cpp file in this folder into build/<name>.
#   make           compile
#   make run       compile and run the programs
#   make clean     remove build/
# Another compiler or optimisation level: make CXX=clang++ OPT=-O2
CXX := g++
OPT := -O0
CXXFLAGS = -std=c++20 $(OPT) -Wall -pthread
SRC := $(wildcard *.cpp)
BIN := $(SRC:%.cpp=build/%)

.PHONY: all run clean

all: $(BIN)

build/%: %.cpp $(wildcard *.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	@for b in $(BIN); do echo "== $$b"; ./$$b; done

clean:
	rm -rf build
