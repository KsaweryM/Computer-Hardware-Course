// lobby.h: ready functions for the game server. We do not look inside.
#pragma once
#include <chrono>
#include <cstdio>
#include <thread>

const int PLAYERS = 4;       // a match needs 4 players

// wait ms milliseconds
void pause(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// the player loads the map: player 0 takes 1 s, player 1 takes 1.5 s, ... player 3 takes 2.5 s
void load_map(int id) {
    pause(1000 + 500 * id);
    printf("player %d: map loaded\n", id);
}

// the match starts for this player
void start_match(int id) { printf("player %d: the match starts!\n", id); }
