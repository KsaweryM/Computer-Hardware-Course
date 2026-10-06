// tickets.h: ready functions for the ticket shop. We do not look inside.
#pragma once
#include <chrono>
#include <thread>

const int SEATS = 100;       // the hall has 100 seats
const int CUSTOMERS = 150;   // more people want a ticket than there are seats

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// the customer pays: the shop talks to the bank, takes 10 ms
void pay() { pause(10); }
