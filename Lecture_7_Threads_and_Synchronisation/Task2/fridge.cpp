// Task 2: lock the fridge. This is the program from Task 1.
// TODO: add a mutex, so that the fridge is never overfull.
#include <iostream>
#include <thread>
#include "office.h"

int fridge = CAPACITY;     // sandwiches in the fridge

void worker(int want, int pause_ms) {
    for (int i = 0; i < MEALS; i++) {
        if (fridge >= want) {
            fridge = fridge - want;        // eat
        } else {
            int buy = CAPACITY - fridge + want;
            go_to_shop();
            fridge = fridge + buy - want;  // eat, rest in
        }
        pause(pause_ms);
    }
}

void cleaner() {
    for (int i = 0; i < 400; i++) {        // 4 s
        if (fridge > CAPACITY)
            std::cout << "the fridge is "
                      << "overfull: "
                      << fridge << "\n";
        pause(10);
    }
}

int main() {
    std::thread w0(worker, 3, 30);
    std::thread w1(worker, 4, 40);
    std::thread w2(worker, 5, 50);
    std::thread c(cleaner);
    w0.join(); w1.join(); w2.join(); c.join();
}
