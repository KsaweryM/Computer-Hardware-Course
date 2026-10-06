// Task 1: the office fridge.
// Three workers share one fridge. A cleaner checks that it is not overfull.
#include <iostream>
#include <thread>
#include "office.h"

int fridge = CAPACITY;     // sandwiches in the fridge

// The rule for every worker:
//   1. Look into the fridge.
//   2. Enough sandwiches? Take yours and eat.
//   3. Not enough?
//      - make a shopping list: buy exactly enough to eat what you want and leave the fridge full;
//      - go to the shop: go_to_shop();
//      - eat as many as you want, put the rest into the fridge.
void worker(int want, int pause_ms) {
    // TODO 1: MEALS times: follow the rule, then pause(pause_ms)
}

void cleaner() {
    // TODO 2: every 10 ms, for 4 s, look into the fridge.
    //         More than CAPACITY? Print: the fridge is overfull: <how many>
}

int main() {
    // TODO 3: start 4 threads and join them:
    //         worker(3, 30), worker(4, 40), worker(5, 50), cleaner()
}
