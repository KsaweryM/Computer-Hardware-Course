// office.h: ready functions for the office. We do not look inside.
#pragma once
#include <chrono>
#include <thread>

const int MEALS = 20;      // every worker eats 20 times

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

void take_out() { pause(1); }   // take the food out of the fridge: 1 ms
void heat()     { pause(1); }   // heat it in the microwave: 1 ms
void put_in()   { pause(1); }   // put the rest into the fridge: 1 ms
