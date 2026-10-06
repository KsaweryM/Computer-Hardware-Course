// The engine factory: three lines, one shared counter, no protection.
// Compile with -O0 (the Makefile does it) and run it a few times.
#include <iostream>
#include <thread>

int engines = 0;        // engines in the warehouse

void line() {
    for (int i = 0; i < 1000000; i++)
        engines++;      // one more engine
}

int main() {
    std::thread l0(line), l1(line), l2(line);
    l0.join(); l1.join(); l2.join();
    std::cout << "in stock: " << engines << "\n";
}
