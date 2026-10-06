// warehouse.h: ready functions for Task 7. We do not look inside.
#pragma once
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

const int CAPACITY = 10;   // room in the warehouse
const int ENGINES = 100;   // every line builds 100 engines (3 lines)
const int SALES = 150;     // every seller sells 150 engines (2 sellers)

extern int stock;          // engines in the warehouse, in warehouse.cpp

namespace hidden {
    std::atomic<int> built{0}, sold{0};
    int bad = 0;           // how many times stock was below 0 or above CAPACITY
}

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

void build_engine() { pause(2); hidden::built++; }   // build one engine: 2 ms
void sell_engine()  { pause(5); hidden::sold++; }    // sell one engine: 5 ms

// call it after every change of stock, while you hold the lock
void check() { if (stock < 0 || stock > CAPACITY) hidden::bad++; }

// prints what happened
void report() {
    std::cout << "built: " << hidden::built << ", sold: " << hidden::sold << ", in stock: " << stock << ",\n"
              << "stock below 0 or above " << CAPACITY << ": " << hidden::bad << " times\n";
}
