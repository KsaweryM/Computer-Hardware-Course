// Task 5: atomic, and a better idea.
// Make two more versions of the counter and measure the time of each:
// 1. atomic: std::atomic<int> counter, without the mutex.
// 2. local sum: each thread counts in its own local variable,
//    and adds it to counter once, at the end (with the mutex).
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int counter = 0;              // TODO 1: try std::atomic<int> counter{0}; (#include <atomic>)
std::mutex m;
const int N = 1'000'000;

void work() {
    // TODO 2: count in a local variable, and add it to counter once, under the mutex
    for (int i = 0; i < N; i++) {
        std::lock_guard<std::mutex> lock(m);
        counter++;
    }
}

int main() {
    auto start = std::chrono::steady_clock::now();
    std::thread a(work), b(work);
    a.join();  b.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;

    std::cout << "Goal: " << 2 * N << "\n";
    std::cout << "Got:  " << counter << "\n";
    std::cout << ms.count() << " ms\n";
}
