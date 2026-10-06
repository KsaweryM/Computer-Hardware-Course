CXX      := g++
CXXFLAGS := -std=c++20 -Wall -O2

app: main.o util.o
	$(CXX) $^ -o $@

main.o: main.cpp util.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
