// bell.h: ready functions for Task 6. We do not look inside.
#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// worker id goes to lunch
void go_to_lunch(int id) { std::cout << "worker " + std::to_string(id) + " goes to lunch\n"; }
