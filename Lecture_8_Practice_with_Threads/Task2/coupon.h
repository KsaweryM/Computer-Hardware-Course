// coupon.h: ready functions for the shop. We do not look inside.
#pragma once
#include <chrono>
#include <thread>

const int MAX_USES = 3;      // the code PROMO50 may be used at most 3 times

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// the shop checks the order (stock, price, address): slow, takes 100 ms
void verify_order() { pause(100); }
