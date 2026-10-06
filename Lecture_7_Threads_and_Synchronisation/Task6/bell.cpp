// Task 6: the lunch bell. This version waits in a loop (busy waiting).
//   1. Run it with time. Write down user and sys.
//   2. Replace busy waiting with a condition_variable. The boss wakes everybody up
//      with notify_all(). Run it with time again.
//   3. Change notify_all() to notify_one(). What happens? Why?
//   If you finish early: put back notify_all() and add pause(3000); at the start of worker().
//   The bell rings before the workers wait. Do they hang? Why not?
#include <mutex>
#include <thread>
#include "bell.h"

bool bell = false;         // has the bell rung?
std::mutex m;

void boss() {
    pause(2000);           // lunch time in 2 s
    m.lock();
    bell = true;           // ring the bell
    m.unlock();
}

void worker(int id) {
    m.lock();
    while (!bell) {        // no bell yet?
        m.unlock();        // let the boss in
        m.lock();          // look again
    }
    m.unlock();
    go_to_lunch(id);
}

int main() {
    std::thread b(boss), w0(worker, 0), w1(worker, 1), w2(worker, 2);
    b.join();
    w0.join(); w1.join(); w2.join();
}
