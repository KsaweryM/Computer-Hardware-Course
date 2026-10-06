// packets.h: the ready part of the program: the speed measurement and the tests. We do not look inside.
// stats.cpp includes it at the top and calls run(TEST, total_bytes, longest_packet) from main().
//   TEST 0: 8 threads send packets of random length; prints millions of packets per second.
//   TEST 1: 8 threads send packets of growing length; checks that on_packet() is correct.
#pragma once
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <thread>
#include <vector>

uint32_t on_packet(uint32_t len);   // written in stats.cpp

const int      THREADS = 8;
const uint32_t PACKETS = 1000000;   // packets per thread

int measure_speed() {
    auto start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (int t = 0; t < THREADS; t++)
        threads.emplace_back([t] {
            uint32_t x = t * 7919 + 1;
            for (uint32_t i = 0; i < PACKETS; i++) {
                x = x * 1103515245u + 12345u;          // a simple random number
                on_packet(64 + (x >> 16) % 1400);      // a packet of 64 to 1463 bytes
            }
        });
    for (auto &th : threads)
        th.join();
    double s = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    printf("%d threads x %u packets: %.2f s, %.1f million packets per second\n",
           THREADS, PACKETS, s, THREADS * (double)PACKETS / s / 1e6);
    printf("To check that your solution is correct, set TEST to 1.\n");
    return 0;
}

int failed = 0;

void check(bool ok, const char *name, const char *why) {
    printf("  [%s] %s", ok ? " OK " : "FAIL", name);
    if (!ok) {
        printf("  ->  %s", why);
        failed++;
    }
    printf("\n");
}

template <typename Bytes, typename Longest>
int run_tests(Bytes &total_bytes, Longest &longest_packet) {
    std::vector<std::vector<uint32_t>> seqs(THREADS);   // the numbers each thread got
    std::vector<long> drops(THREADS, 0);                 // how often longest_packet was below my packet

    std::vector<std::thread> threads;
    for (int t = 0; t < THREADS; t++)
        threads.emplace_back([&, t] {
            seqs[t].reserve(PACKETS);
            for (uint32_t i = 1; i <= PACKETS; i++) {
                uint32_t len = i * THREADS + t;           // growing lengths, mixed between threads
                seqs[t].push_back(on_packet(len));
                if ((uint32_t)longest_packet < len) {     // after my packet, longest_packet must be at least len
                    drops[t]++;
                }
            }
        });
    for (auto &th : threads)
        th.join();

    const uint64_t total = (uint64_t)THREADS * PACKETS;
    uint64_t expected_bytes = 0;
    for (int t = 0; t < THREADS; t++)
        for (uint32_t i = 1; i <= PACKETS; i++)
            expected_bytes += i * THREADS + t;

    std::vector<bool> seen(total, false);
    long duplicates = 0;
    for (auto &v : seqs)
        for (uint32_t s : v) {
            if (s >= total || seen[s]) {
                duplicates++;
            } else {
                seen[s] = true;
            }
        }
    long all_drops = 0;
    for (long d : drops)
        all_drops += d;

    printf("Tests: %d threads x %u packets\n", THREADS, PACKETS);
    check(duplicates == 0, "sequence numbers are unique", "two packets got the same number");
    check((uint64_t)total_bytes == expected_bytes, "byte counter", "some additions to total_bytes were lost");
    check(all_drops == 0, "longest_packet never goes down", "longest_packet lost a longer packet");
    check((uint32_t)longest_packet == THREADS * PACKETS + THREADS - 1, "longest_packet at the end", "wrong maximum");
    printf(failed ? "\nFAILED: %d test(s)\n" : "\nAll tests passed\n", failed);
    return failed != 0;
}

// TEST 0: measure the speed, TEST 1: run the tests. total_bytes and longest_packet may be plain or std::atomic.
template <typename Bytes, typename Longest>
int run(int test, Bytes &total_bytes, Longest &longest_packet) {
    if (test == 0) {
        return measure_speed();
    }
    return run_tests(total_bytes, longest_packet);
}
