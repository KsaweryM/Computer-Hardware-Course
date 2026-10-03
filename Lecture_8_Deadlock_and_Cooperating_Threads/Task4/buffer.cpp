// buffer.cpp: the bounded buffer. The producer is ready: write consumer().
// 1. The consumer takes ITEMS numbers from the buffer and adds them up. Expected sum: 500500.
// 2. In the producer, print a message when it has to wait (the buffer is full). Try SIZE = 1 and SIZE = 100.
// 3. What happens if you forget notFull.notify_one() in the consumer?
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

const int SIZE = 5, ITEMS = 1000;
std::queue<int> buffer;
std::mutex m;
std::condition_variable notFull, notEmpty;

void producer() {
    for (int i = 1; i <= ITEMS; i++) {
        std::unique_lock<std::mutex> lock(m);
        notFull.wait(lock,
            [] { return buffer.size() < SIZE; });
        buffer.push(i);
        notEmpty.notify_one();
    }
}

long long consumer() {
    long long sum = 0;
    // TODO: take ITEMS numbers from the buffer: wait on notEmpty, read and pop, notify notFull
    return sum;
}

int main() {
    long long sum = 0;
    std::thread p(producer);
    std::thread c([&sum] { sum = consumer(); });
    p.join();
    c.join();
    std::cout << "Sum: " << sum << " (expected 500500)\n";
}
