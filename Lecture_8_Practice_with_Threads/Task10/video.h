// video.h: ready functions for the video driver. We do not look inside.
#pragma once
#include <chrono>
#include <cstdio>
#include <thread>

const int FRAMES = 100;      // the video has 100 frames: 4 s at 25 frames per second

struct Frame {
    int number;              // 0, 1, 2, ...
    bool key;                // a key frame (I-frame): slow to decode
};

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// decode frame i: a normal frame takes 5 ms, every 25th frame is a key frame and takes 200 ms
Frame decode_frame(int i) {
    bool key = (i % 25 == 0);
    pause(key ? 200 : 5);
    return Frame{i, key};
}

int freezes = 0;             // how many times the picture froze
std::chrono::steady_clock::time_point last_shown;   // when the last frame left the screen

// show the frame on the screen: 40 ms (25 frames per second).
// If it comes more than 10 ms after the previous frame left the screen, the picture froze.
void show(Frame f) {
    auto now = std::chrono::steady_clock::now();
    if (f.number > 0) {
        long late = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_shown).count();
        if (late > 10) {
            freezes++;
            printf("display: frame %d is %ld ms late, the picture freezes\n", f.number, late);
        }
    }
    pause(40);
    last_shown = std::chrono::steady_clock::now();
}

// print a summary at the end
void report() { printf("the video is over: %d frames, the picture froze %d times\n", FRAMES, freezes); }
