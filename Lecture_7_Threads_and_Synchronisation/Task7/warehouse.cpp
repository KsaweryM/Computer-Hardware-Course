// Task 7: the warehouse. This version waits in a loop (busy waiting).
//   1. Run it with time. Write down user and sys.
//   2. Replace busy waiting with a condition_variable, in seller() and in line().
//      Run it with time.
//   3. Is it still correct?
//   4. Change while to if. Run it 3 times. What happens? Why?
//   5. Remove notify_all(). What happens? Why?
#include <mutex>
#include <thread>
#include "warehouse.h"

int stock = 0;             // engines in the warehouse
std::mutex m;

void line() {
    for (int i = 0; i < ENGINES; i++) {
        build_engine();
        m.lock();
        while (stock == CAPACITY) {   // full?
            m.unlock();               // let a seller in
            m.lock();                 // look again
        }
        stock++;
        check();
        m.unlock();
    }
}

void seller() {
    for (int i = 0; i < SALES; i++) {
        m.lock();
        while (stock == 0) {   // empty?
            m.unlock();        // let a line in
            m.lock();          // look again
        }
        stock--;
        check();
        m.unlock();
        sell_engine();
    }
}

int main() {
    std::thread l0(line), l1(line), l2(line);
    std::thread s0(seller), s1(seller);
    l0.join(); l1.join(); l2.join();
    s0.join(); s1.join();
    report();
}
