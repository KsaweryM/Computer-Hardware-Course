// pipeline.cpp: Mini-project 2, a pipeline.
// Three threads connected by two bounded buffers:
//   generate the numbers 1 to N  ->  square them  ->  add them up
// Check the result: 1^2 + 2^2 + ... + N^2 = N(N+1)(2N+1)/6. For N = 1000: 333833500.
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

const int SIZE = 5;          // the places in each buffer
const long long N = 1000;    // how many numbers

// A bounded buffer, as in Task 4, packed into a class.
class Buffer {
public:
    void push(long long x) {
        // TODO 1: wait until there is a free place, push x, wake up the consumer
    }
    long long pop() {
        // TODO 2: wait until there is an item, take it out, wake up the producer, return it
        return 0;
    }
private:
    std::queue<long long> q;
    std::mutex m;
    std::condition_variable notFull, notEmpty;
};

Buffer numbers, squares;     // generate -> numbers -> square -> squares -> add

void generate() {
    // TODO 3: push 1, 2, ..., N into numbers
}

void square() {
    // TODO 4: N times: take x from numbers, push x * x into squares
}

long long add() {
    long long sum = 0;
    // TODO 5: N times: take a value from squares and add it to sum
    return sum;
}

int main() {
    long long sum = 0;
    std::thread g(generate), s(square);
    std::thread a([&sum] { sum = add(); });
    g.join();  s.join();  a.join();
    std::cout << "Sum:      " << sum << "\n";
    std::cout << "Expected: " << N * (N + 1) * (2 * N + 1) / 6 << "\n";
}
