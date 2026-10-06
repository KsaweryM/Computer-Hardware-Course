#include <condition_variable>
#include <cstdio>
#include <mutex>
#include <queue>
#include <thread>
#include "video.h"

const int CAPACITY = 10;     // the buffer holds at most 10 frames

std::queue<Frame> buffer;
bool finished = false;       // the decoder has decoded the last frame
std::mutex m;
std::condition_variable not_full;    // the decoder waits here when it is full
std::condition_variable not_empty;   // the display waits here when it is empty

void decoder() {             // the producer
    for (int i = 0; i < FRAMES; i++) {
        Frame f = decode_frame(i);
        std::unique_lock<std::mutex> lock(m);
        while ((int)buffer.size() == CAPACITY)
            not_full.wait(lock);             // sleep until the display takes a frame
        buffer.push(f);
        not_empty.notify_one();              // the display may be waiting for a frame
    }
    std::lock_guard<std::mutex> lock(m);
    finished = true;                         // nothing more comes
    not_empty.notify_one();                  // the display may be asleep
    printf("decoder: all frames decoded\n");
}

void display() {             // the consumer
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        while (buffer.empty() && !finished)
            not_empty.wait(lock);            // until a frame comes or the end
        if (buffer.empty()) {                // finished and nothing left: the end
            return;
        }
        Frame f = buffer.front();
        buffer.pop();
        not_full.notify_one();               // the decoder may be waiting for space
        lock.unlock();
        show(f);                             // 40 ms, not under the mutex
    }
}

int main() {
    std::thread d(decoder), s(display);
    d.join();
    s.join();
    report();
}
