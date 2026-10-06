// Two workers, two locks, two orders. Run it a few times: does it finish?
// It may hang: stop it with Ctrl+C.
#include <iostream>
#include <mutex>
#include <thread>
#include "office.h"

std::mutex fridge_m;   // the fridge
std::mutex micro_m;    // the microwave

void lunch() {    // take it out, then heat it
    for (int i = 0; i < MEALS; i++) {
        fridge_m.lock();      // 1. fridge
        take_out();
        micro_m.lock();       // 2. microwave
        heat();
        micro_m.unlock();
        fridge_m.unlock();
        pause(30);
    }
}

void soup() {     // heat it, then put rest in
    for (int i = 0; i < MEALS; i++) {
        micro_m.lock();       // 1. microwave
        heat();
        fridge_m.lock();      // 2. fridge
        put_in();
        fridge_m.unlock();
        micro_m.unlock();
        pause(40);
    }
}

int main() {
    std::thread a(lunch), b(soup);
    a.join(); b.join();
    std::cout << "all done\n";
}
