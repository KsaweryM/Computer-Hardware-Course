// Task 4: fix it with a mutex, and measure.
// 1. Add a mutex. Is the result correct now?
// 2. Measure the time without and with the mutex.
// 3. How many times slower is the correct version?
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int counter = 0;
const int N = 1'000'000;
// TODO 1: a std::mutex

void work() {
    for (int i = 0; i < N; i++)
        counter++;              // TODO 2: protect this line with a std::lock_guard
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
