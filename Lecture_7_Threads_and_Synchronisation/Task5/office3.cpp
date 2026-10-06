// Task 5: fix office A. This is office A from Task 4: it can hang.
//   1. Fix it with one order: change only main().
//   2. Fix it with scoped_lock: change only worker().
//   3. Run each fix 3 times. Does it hang?
//   4. Which fix works without knowing the other workers?
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include "office.h"

std::mutex fridge_m, micro_m, kettle_m;

void worker(std::mutex &first, std::mutex &second, int pause_ms) {
    for (int i = 0; i < MEALS; i++) {
        first.lock();   use();
        second.lock();  use();
        second.unlock();
        first.unlock();
        pause(pause_ms);
    }
}

int main() {
    // std::ref: the thread gets the mutex itself, not a copy
    std::thread w0(worker, std::ref(fridge_m), std::ref(micro_m), 30);
    std::thread w1(worker, std::ref(micro_m), std::ref(kettle_m), 40);
    std::thread w2(worker, std::ref(kettle_m), std::ref(fridge_m), 50);
    w0.join(); w1.join(); w2.join();
    std::cout << "all done\n";
}
