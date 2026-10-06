// gpu.h: ready functions for the GPU. We do not look inside.
#pragma once
#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>

const int UNITS = 3;         // the GPU has 3 hardware decoding units
const int STREAMS = 6;       // 6 videos play at the same time

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

std::atomic<int> busy{0};    // decoding units in use now
std::atomic<int> errors{0};  // hardware errors so far

// decode one stream on a free unit: takes 1 s.
// If all 3 units are in use, the hardware reports an error.
void decode(int id) {
    int n = ++busy;
    if (n > UNITS) {
        errors++;
        printf("stream %d: HARDWARE ERROR, %d streams want %d units\n", id, n, UNITS);
    } else {
        printf("stream %d: decoding on a unit (%d of %d busy)\n", id, n, UNITS);
    }
    pause(1000);
    busy--;
}

// print a summary at the end
void report() { printf("all streams done, hardware errors: %d\n", errors.load()); }
