#include <thread>
#include <vector>
#include "gpu.h"

void decode_stream(int id) {
    decode(id);
}

int main() {
    std::vector<std::thread> threads;
    for (int id = 0; id < STREAMS; id++)
        threads.emplace_back(decode_stream, id);
    for (auto &t : threads)
        t.join();
    report();
}
