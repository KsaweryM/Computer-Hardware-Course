// Task 4: who waits for whom?
// Three offices, three workers in each, three machines. Set OFFICE in main() to 'A', 'B' or 'C'.
//   1. For each office, draw who can wait for whom.
//   2. Which offices can hang? Answer before you run it.
//   3. Run each office 3 times (Ctrl+C stops a program that hangs). Were you right?
//   4. Office A with only two of the three workers: can it hang?
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

// std::ref: the thread gets the mutex itself, not a copy
void office_a() {
    std::thread w0(worker, std::ref(fridge_m), std::ref(micro_m), 30);
    std::thread w1(worker, std::ref(micro_m), std::ref(kettle_m), 40);
    std::thread w2(worker, std::ref(kettle_m), std::ref(fridge_m), 50);
    w0.join(); w1.join(); w2.join();
}

void office_b() {
    std::thread w0(worker, std::ref(fridge_m), std::ref(micro_m), 30);
    std::thread w1(worker, std::ref(micro_m), std::ref(kettle_m), 40);
    std::thread w2(worker, std::ref(fridge_m), std::ref(kettle_m), 50);
    w0.join(); w1.join(); w2.join();
}

void office_c() {
    std::thread w0(worker, std::ref(fridge_m), std::ref(micro_m), 30);
    std::thread w1(worker, std::ref(kettle_m), std::ref(micro_m), 40);
    std::thread w2(worker, std::ref(kettle_m), std::ref(fridge_m), 50);
    w0.join(); w1.join(); w2.join();
}

int main() {
    const char OFFICE = 'A';   // 'A', 'B' or 'C'
    if (OFFICE == 'A') office_a();
    if (OFFICE == 'B') office_b();
    if (OFFICE == 'C') office_c();
    std::cout << "all done\n";
}
