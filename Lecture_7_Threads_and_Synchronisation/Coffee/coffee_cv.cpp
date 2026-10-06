// Coffee: the version with a condition_variable from the lecture.
#include <condition_variable>
#include <mutex>
#include <thread>
#include "coffee.h"

bool ready = false;        // is the coffee ready?
std::mutex m;
std::condition_variable cv;

void machine() {
    make_coffee(2000);     // takes 2 s
    std::lock_guard<std::mutex> g(m);
    ready = true;
    cv.notify_one();       // wake the worker up
}

void worker() {
    std::unique_lock<std::mutex> lk(m);
    while (!ready)         // not ready?
        cv.wait(lk);       // sleep until notify
    drink_coffee();
}

int main() {
    std::thread c(machine), w(worker);
    c.join();
    w.join();
}
