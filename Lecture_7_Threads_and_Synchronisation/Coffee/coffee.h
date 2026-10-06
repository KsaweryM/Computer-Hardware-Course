// coffee.h: ready functions for the coffee example. We do not look inside.
#pragma once
#include <chrono>
#include <iostream>
#include <thread>

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// the machine makes a coffee: takes ms milliseconds
void make_coffee(int ms) { pause(ms); std::cout << "machine: the coffee is ready\n"; }

// the worker drinks the coffee
void drink_coffee() { std::cout << "worker: I drink the coffee\n"; }
