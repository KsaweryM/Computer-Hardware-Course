#include <cstdio>
#include <mutex>
#include <queue>
#include <thread>
#include "video.h"

const int CAPACITY = 10;     // the buffer holds at most 10 frames

std::queue<Frame> buffer;
std::mutex m;

void decoder() {             // the producer
    for (int i = 0; i < FRAMES; i++) {
        Frame f = decode_frame(i);
        m.lock();
        while ((int)buffer.size() == CAPACITY) {   // full? look again
            m.unlock();
            m.lock();
        }
        buffer.push(f);
        m.unlock();
    }
    printf("decoder: all frames decoded\n");
}

void display() {             // the consumer
    while (true) {
        m.lock();
        while (buffer.empty()) {                   // empty? look again
            m.unlock();
            m.lock();
        }
        Frame f = buffer.front();
        buffer.pop();
        m.unlock();
        show(f);
    }
}

int main() {
    std::thread d(decoder), s(display);
    d.join();
    s.join();
    report();
}
