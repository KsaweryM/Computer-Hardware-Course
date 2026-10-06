// The engine factory, fixed with an atomic variable.
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> engines = 0;

void line() {
    for (int i = 0; i < 1000000; i++)
        engines++;
}

int main() {
    std::thread l0(line), l1(line), l2(line);
    l0.join(); l1.join(); l2.join();
    std::cout << "in stock: " << engines << "\n";
}
