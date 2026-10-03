// bank.cpp: step 3. Fix it: step 4 (increasing order) and step 5 (std::scoped_lock).
// The sum of all balances must always be 10000.
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>

const int ACCOUNTS = 10, THREADS = 4;
const int TRANSFERS = 1'000'000 / THREADS;
int balance[ACCOUNTS];
std::mutex m[ACCOUNTS];

void transfers(int id) {
    std::mt19937 rng(id);
    std::uniform_int_distribution<int>
        acc(0, ACCOUNTS - 1), amount(1, 100);
    for (int i = 0; i < TRANSFERS; i++) {
        int from = acc(rng), to = acc(rng);
        if (from == to) continue;
        int x = amount(rng);
        std::lock_guard<std::mutex> a(m[from]);
        std::lock_guard<std::mutex> b(m[to]);
        balance[from] -= x;
        balance[to]   += x;
        if (i % 50'000 == 0)
            std::cout << id << ": " << i << "\n";
    }
}

int main() {
    for (int i = 0; i < ACCOUNTS; i++)
        balance[i] = 1000;

    auto start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (int t = 0; t < THREADS; t++)
        threads.emplace_back(transfers, t);
    for (auto &t : threads)
        t.join();
    auto end = std::chrono::steady_clock::now();

    int sum = 0;
    for (int i = 0; i < ACCOUNTS; i++)
        sum += balance[i];
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "Sum: " << sum << "   time: " << ms.count() << " ms\n";
}
