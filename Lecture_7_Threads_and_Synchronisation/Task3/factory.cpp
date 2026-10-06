// Task 3: an order for 1000 engines.
//   1. A customer orders exactly ORDER engines: not one more, not one less.
//   2. Every engine gets its own serial number: 1, 2, ..., 1000. No number twice.
//   3. Use std::atomic, no mutex.
//   4. Count in built_by[id] how many engines each line built.
#include <atomic>
#include "factory.h"

int built_by[3];   // engines built by each line

void line(int id, int build_ms) {
    // TODO: build engines with build_engine(serial, build_ms) until the order is done
}

int main() {
    std::thread l0(line, 0, 1);  // fast
    std::thread l1(line, 1, 2);
    std::thread l2(line, 2, 3);  // slow
    l0.join(); l1.join(); l2.join();
    check_order();
    for (int id = 0; id < 3; id++)
        std::cout << "line " << id << " built " << built_by[id] << " engines\n";
}
