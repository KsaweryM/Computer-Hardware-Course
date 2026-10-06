// table.h: ready functions for the dining philosophers. We do not look inside.
#pragma once
#include <atomic>
#include <chrono>
#include <cstdio>
#include <mutex>
#include <thread>

const int N = 5;             // 5 philosophers, 5 forks
const int SECONDS = 3;       // the dinner lasts 3 s

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

std::atomic<bool> dinner_over{false};   // becomes true after SECONDS
int meals[N] = {0};                     // how many times each philosopher has eaten

// philosopher id thinks: 0 to 9 ms
void think(int id) { pause((id * 7 + meals[id] * 3) % 10); }

// pick up a fork: lock its mutex
void pick_up(std::mutex &fork) { fork.lock(); }

// philosopher id eats: 5 ms
void eat(int id) { pause(5); meals[id]++; }

// the end of the dinner, after SECONDS
void wait_for_end() { pause(SECONDS * 1000); dinner_over = true; }

// print how many times each philosopher has eaten
void report() {
    printf("meals:");
    for (int i = 0; i < N; i++) printf("  P%d: %d", i, meals[i]);
    printf("\n");
}
