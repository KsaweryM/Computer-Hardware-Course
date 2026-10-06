// office.h: ready functions for the office. We do not look inside.
#pragma once
#include <chrono>
#include <thread>

const int MEALS = 20;      // every worker eats 20 times

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// use a machine (the fridge, the microwave or the kettle): 1 ms
void use() { pause(1); }
