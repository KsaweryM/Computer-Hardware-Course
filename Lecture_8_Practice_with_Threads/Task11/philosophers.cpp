#include <mutex>
#include <thread>
#include <vector>
#include "table.h"

std::mutex forks[N];         // fork i: between philosopher i - 1 and philosopher i

void philosopher(int id) {
    int left = id;               // the fork on my left
    int right = (id + 1) % N;    // the fork on my right
    while (!dinner_over) {
        think(id);
        pick_up(forks[left]);
        pick_up(forks[right]);
        eat(id);
        forks[right].unlock();
        forks[left].unlock();
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int id = 0; id < N; id++)
        threads.emplace_back(philosopher, id);
    wait_for_end();
    for (auto &t : threads)
        t.join();
    report();
}
