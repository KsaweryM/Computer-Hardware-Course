// turns.h: ready functions. We do not look inside.
#pragma once
#include <chrono>
#include <cstdio>
#include <thread>

const int ROUNDS = 10;       // every thread says its letter 10 times

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// print the letter: takes 300 ms
void say(char name) {
    printf("%c ", name);
    fflush(stdout);
    pause(300);
}
