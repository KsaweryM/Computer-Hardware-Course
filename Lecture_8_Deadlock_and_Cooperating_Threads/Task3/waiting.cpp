// waiting.cpp: main prepares the data for 3 seconds, then sets ready.
// The worker waits for it and prints how late it reacted.
// Version 1: busy waiting. Then write version 2 (sleep and check) and version 3 (a condition variable).
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using Clock = std::chrono::steady_clock;
std::atomic<bool> ready{false};
Clock::time_point readyAt;

void worker() {
    while (!ready) { }                       // version 1: busy waiting
    std::chrono::duration<double, std::milli> late = Clock::now() - readyAt;
    std::cout << "The worker reacted " << late.count() << " ms late\n";
}

int main() {
    std::thread w(worker);
    std::this_thread::sleep_for(std::chrono::seconds(3));   // prepare the data
    readyAt = Clock::now();
    ready = true;
    w.join();
}
