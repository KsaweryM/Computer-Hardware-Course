// To check that your solution is correct, change TEST from 0 to 1.
const int TEST = 0;

#include <cstdint>
#include <mutex>
#include "packets.h"     // ready: the speed measurement and the tests

std::mutex m;
uint32_t packet_count   = 0;  // how many packets so far; the next packet gets this number
uint64_t total_bytes    = 0;  // the length of all packets together
uint32_t longest_packet = 0;  // the length of the longest packet so far

// called for every packet; returns its sequence number
uint32_t on_packet(uint32_t len) {
    std::lock_guard<std::mutex> lock(m);
    uint32_t number = packet_count++;
    total_bytes += len;
    if (len > longest_packet) {
        longest_packet = len;
    }
    return number;
}

int main() {
    // TEST 0: measure the speed, TEST 1: run the tests
    return run(TEST, total_bytes, longest_packet);
}
