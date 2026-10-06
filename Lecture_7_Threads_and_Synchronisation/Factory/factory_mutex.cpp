// The engine factory, fixed with a mutex.
#include <iostream>
#include <mutex>
#include <thread>

int engines = 0;        // engines in the warehouse
std::mutex m;

void line() {
    for (int i = 0; i < 1000000; i++) {
        m.lock();
        engines++;
        m.unlock();
    }
}

int main() {
    std::thread l0(line), l1(line), l2(line);
    l0.join(); l1.join(); l2.join();
    std::cout << "in stock: " << engines << "\n";
}
