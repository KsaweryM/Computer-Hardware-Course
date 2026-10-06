// office.h: ready functions for the office. We do not look inside.
#pragma once
#include <chrono>
#include <thread>

const int CAPACITY = 10;   // the fridge holds at most 10 sandwiches
const int MEALS = 20;      // every worker eats 20 times

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// go to the shop and come back: takes 50 ms
void go_to_shop() { pause(50); }
