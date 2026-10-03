// philosophers.cpp: five philosophers, five forks (mutexes).
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

const int P = 5, MEALS = 1000;
std::mutex fork_[P];
int meals[P];

void philosopher(int i) {
    int left = i, right = (i + 1) % P;
    for (int k = 0; k < MEALS; k++) {
        std::lock_guard<std::mutex> a(fork_[left]);
        // look around
        std::lock_guard<std::mutex> b(fork_[right]);
        meals[i]++;                       // eat
    }
}

int main() {
    std::vector<std::thread> ph;
    for (int i = 0; i < P; i++)
        ph.emplace_back(philosopher, i);
    for (auto &t : ph)
        t.join();
    for (int i = 0; i < P; i++)
        std::cout << "Philosopher " << i << " ate " << meals[i] << " times\n";
}
