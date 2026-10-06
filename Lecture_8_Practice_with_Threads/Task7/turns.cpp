#include <cstdio>
#include <mutex>
#include <thread>
#include <vector>
#include "turns.h"

const int THREADS = 3;

int turn = 0;                // whose turn it is: 0 = A, 1 = B, 2 = C
std::mutex m;

void player(int id) {
    char name = 'A' + id;
    for (int i = 0; i < ROUNDS; i++) {
        m.lock();
        while (turn != id) {     // not my turn? ask again
            m.unlock();
            m.lock();
        }
        m.unlock();
        say(name);               // takes 300 ms: not under the mutex
        m.lock();
        turn = (turn + 1) % THREADS;
        m.unlock();
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int id = 0; id < THREADS; id++)
        threads.emplace_back(player, id);
    for (auto &t : threads)
        t.join();
    printf("\n");
}
