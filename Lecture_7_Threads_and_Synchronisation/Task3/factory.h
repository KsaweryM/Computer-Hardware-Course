// factory.h: ready functions for Task 3. We do not look inside.
#pragma once
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int ORDER = 1000;    // the customer orders exactly 1000 engines

namespace hidden {
    std::mutex m;
    std::vector<int> built;          // serial numbers, in the order of building
}

// builds one engine with this serial number; takes ms milliseconds
void build_engine(int serial, int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    std::lock_guard<std::mutex> g(hidden::m);
    hidden::built.push_back(serial);
}

// is the order OK? prints how many engines were built and which serial numbers are wrong
void check_order() {
    std::vector<int> count(ORDER + 100000, 0);
    int bad = 0;
    for (int s : hidden::built) {
        if (s < 1 || s >= (int)count.size()) { bad++; continue; }
        count[s]++;
    }
    int twice = 0, missing = 0;
    for (int s = 1; s <= ORDER; s++) {
        if (count[s] == 0) missing++;
        if (count[s] > 1) twice++;
    }
    int extra = 0;
    for (int s = ORDER + 1; s < (int)count.size(); s++) extra += count[s];
    std::cout << "engines built: " << hidden::built.size() << " (order: " << ORDER << ")\n";
    std::cout << "serial numbers used twice: " << twice << ",\n    missing: " << missing
              << ", above " << ORDER << ": " << extra + bad << "\n";
    bool ok = hidden::built.size() == ORDER && twice == 0 && missing == 0 && extra + bad == 0;
    std::cout << (ok ? "order OK\n" : "order WRONG\n");
}
