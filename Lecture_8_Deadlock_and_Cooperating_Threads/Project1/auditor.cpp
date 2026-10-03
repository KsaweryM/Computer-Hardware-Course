// auditor.cpp: Mini-project 1, the auditor.
// The bank of step 4 (the lock order), plus one more thread: the auditor.
// While the transfers run, the auditor checks the sum every 100 ms and prints it.
// It must lock ALL accounts, without a deadlock. Hint: the lock order.
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <atomic>
#include <algorithm>

const int ACCOUNTS = 10, THREADS = 4;
const int TRANSFERS = 4'000'000 / THREADS;
int balance[ACCOUNTS];
std::mutex m[ACCOUNTS];
std::atomic<bool> done{false};     // set by main() when all transfers are finished

void transfers(int id) {
    std::mt19937 rng(id);
    std::uniform_int_distribution<int>
        acc(0, ACCOUNTS - 1), amount(1, 100);
    for (int i = 0; i < TRANSFERS; i++) {
        int from = acc(rng), to = acc(rng);
        if (from == to) continue;
        int x = amount(rng);
        int first = std::min(from, to), second = std::max(from, to);
        std::lock_guard<std::mutex> a(m[first]);
        std::lock_guard<std::mutex> b(m[second]);
        balance[from] -= x;
        balance[to]   += x;
    }
}

void auditor() {
    // TODO: until done is true:
    //   1. lock all accounts (in which order?),
    //   2. add up the balances and print the sum,
    //   3. unlock all accounts,
    //   4. sleep for 100 ms.
}

int main() {
    for (int i = 0; i < ACCOUNTS; i++)
        balance[i] = 1000;

    std::thread a(auditor);
    std::vector<std::thread> threads;
    for (int t = 0; t < THREADS; t++)
        threads.emplace_back(transfers, t);
    for (auto &t : threads)
        t.join();
    done = true;
    a.join();

    int sum = 0;
    for (int i = 0; i < ACCOUNTS; i++)
        sum += balance[i];
    std::cout << "Final sum: " << sum << " (expected 10000)\n";
}
