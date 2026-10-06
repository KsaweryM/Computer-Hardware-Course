#include <mutex>
#include <thread>
#include <vector>
#include "lobby.h"

int loaded = 0;              // how many players have loaded the map
std::mutex m;

void player(int id) {
    load_map(id);
    m.lock();
    loaded++;
    while (loaded < PLAYERS) {   // not everybody? ask again
        m.unlock();
        m.lock();
    }
    m.unlock();
    start_match(id);
}

int main() {
    std::vector<std::thread> threads;
    for (int id = 0; id < PLAYERS; id++)
        threads.emplace_back(player, id);
    for (auto &t : threads)
        t.join();
}
