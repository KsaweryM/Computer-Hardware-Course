CXX      := g++
CXXFLAGS := -std=c++20 -Wall -O2
OBJ      := main.o util.o

.PHONY: all run clean

all: app

app: $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp util.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: app
	./app

clean:
	rm -f app $(OBJ)
