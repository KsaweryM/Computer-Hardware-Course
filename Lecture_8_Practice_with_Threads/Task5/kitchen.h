// kitchen.h: ready functions for the pizzeria. We do not look inside.
#pragma once
#include <chrono>
#include <mutex>
#include <thread>

const int PIZZAS = 10;       // every cook makes 10 pizzas

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// take an ingredient: one cook at a time
void take(std::mutex &ingredient) { ingredient.lock(); }

// bake the pizza: 2 ms
void bake() { pause(2); }

// write the number of pizzas on the board: takes 2 ms
void write_on_board() { pause(2); }

// bring the pizza to the table: takes ms milliseconds
void serve(int ms) { pause(ms); }
