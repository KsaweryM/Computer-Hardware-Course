// printers.cpp: a print room with 2 printers.
// 1. Start 8 threads. Each one prints a document: sleep_for(500ms).
//    At most 2 threads may print at the same time: use a std::counting_semaphore.
// 2. Count in a std::atomic<int> inside how many threads are printing right now, and print it. Is it ever more than 2?
// 3. How long does the whole program take? Calculate first, then measure.
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <semaphore>

// TODO 1: a semaphore for 2 printers, and std::atomic<int> inside{0};

void print(int id) {
    // TODO 2: take a printer, print for 500 ms, give the printer back
}

int main() {
    auto start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < 8; i++)
        threads.emplace_back(print, i);
    for (auto &t : threads)
        t.join();
    std::chrono::duration<double> s = std::chrono::steady_clock::now() - start;
    std::cout << "Total: " << s.count() << " s\n";
}
