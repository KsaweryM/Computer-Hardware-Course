// Coffee: the busy-waiting version from the lecture.
#include <mutex>
#include <thread>
#include "coffee.h"

bool ready = false;        // is the coffee ready?
std::mutex m;

void machine() {
    make_coffee(2000);     // takes 2 s
    m.lock();
    ready = true;
    m.unlock();
}

void worker() {
    m.lock();
    while (!ready) {       // not ready?
        m.unlock();        // let the machine in
        m.lock();          // look again
    }
    m.unlock();
    drink_coffee();
}

int main() {
    std::thread c(machine), w(worker);
    c.join();
    w.join();
}
