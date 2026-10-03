// race.cpp: two threads increase one shared counter.
#include <iostream>
#include <thread>

int counter = 0;
const int N = 1'000'000;

void work() {
    for (int i = 0; i < N; i++)
        counter++;
}

int main() {
    std::thread a(work), b(work);
    a.join();  b.join();
    std::cout << "Goal: " << 2 * N << "\n";
    std::cout << "Got:  " << counter << "\n";
}
