#include <iostream>
#include <thread>
#include <vector>
#include "coupon.h"

const int CLICKS = 100;      // how many people click "Use code" at the same time

int used = 0;                // how many times the code was used

// returns true if the discount was given
bool redeem() {
    if (used >= MAX_USES) {  // 1. check: is the limit used up?
        return false;
    }
    verify_order();          //    (slow)
    used++;                  // 2. act: count this use
    return true;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < CLICKS; i++)
        threads.emplace_back(redeem);
    for (auto &t : threads)
        t.join();
    std::cout << CLICKS << " clicks, the code was used " << used
              << " times (limit " << MAX_USES << ")\n";
}
