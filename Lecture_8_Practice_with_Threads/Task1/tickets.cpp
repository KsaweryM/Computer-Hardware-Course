#include <iostream>
#include <thread>
#include <vector>
#include "tickets.h"

int tickets = SEATS;              // tickets left
bool got[CUSTOMERS] = {false};    // did the customer get a ticket?

void customer(int id) {
    if (tickets > 0) {            // 1. check: any tickets left?
        pay();                    //    (the customer pays)
        tickets--;                // 2. act: buy
        got[id] = true;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int id = 0; id < CUSTOMERS; id++)
        threads.emplace_back(customer, id);
    for (auto &t : threads)
        t.join();

    std::cout << "tickets left: " << tickets << "\n";
}
