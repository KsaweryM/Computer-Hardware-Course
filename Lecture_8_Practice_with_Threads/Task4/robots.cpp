//
//   #   #   ###        #   #  #####  #####  ####
//   ##  #  #   #       ##  #  #      #      #   #
//   # # #  #   #       # # #  ####   ####   #   #
//   #  ##  #   #       #  ##  #      #      #   #
//   #   #   ###        #   #  #####  #####  ####
//
//   #####   ###        ####   #####   ###   ####
//     #    #   #       #   #  #      #   #  #   #
//     #    #   #       ####   ####   #####  #   #
//     #    #   #       #  #   #      #   #  #   #
//     #     ###        #   #  #####  #   #  ####
//
//   #####  #   #  #####   ####        ####   ###   ####   #####
//     #    #   #    #    #           #      #   #  #   #  #
//     #    #####    #     ###        #      #   #  #   #  ####
//     #    #   #    #        #       #      #   #  #   #  #
//     #    #   #  #####  ####         ####   ###   ####   #####
//
// The warehouse of Task 4. This program is ready: change only routes.txt.
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <latch>
#include <memory>
#include <mutex>
#include <semaphore>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

const int ROWS = 5;
const int COLS = 8;
const int STUCK_MS = 2000;   // waiting longer than this counts as stuck

struct Cell { int r, c; };

struct Robot {
    char name;
    Cell pos;                // where it stands now
    std::string route;       // R, L, U, D
    int step_ms;             // time for one step
    // state read by other threads, protected by state_m
    bool waiting = false;
    Cell want{-1, -1};       // the cell it waits for
    bool finished = false;
    bool swapped = false;    // another robot has done a swap for both of us (safety rule)
    std::chrono::steady_clock::time_point since;   // waiting since
};

// The lock of one cell. It works like a mutex, but any thread may unlock it: after a swap (safety rule)
// each robot stands on the cell that the other robot locked.
struct CellLock {
    std::binary_semaphore s{1};
    bool try_lock() { return s.try_acquire(); }
    void lock() { s.acquire(); }
    void unlock() { s.release(); }
};

CellLock cell_m[ROWS][COLS];           // one lock per cell
std::mutex state_m;                    // protects the fields of all robots and the printing
std::vector<Robot> robots;
bool safety = false;                   // the engineers' safety rule (question 4)
std::unique_ptr<std::latch> start;    // all robots stand on their start cells before anyone moves

// who stands on cell x? -1 if nobody; call with state_m locked
int who_is_at(Cell x) {
    for (size_t i = 0; i < robots.size(); i++) {
        if (!robots[i].finished && robots[i].pos.r == x.r && robots[i].pos.c == x.c) {
            return (int)i;
        }
    }
    return -1;
}

// print the grid; call with state_m locked
void print_grid() {
    for (int r = 0; r < ROWS; r++) {
        std::string line = "  ";
        for (int c = 0; c < COLS; c++) {
            int i = who_is_at({r, c});
            line += (i < 0 ? '.' : robots[i].name);
            line += ' ';
        }
        std::cout << line << "\n";
    }
    std::cout << "\n" << std::flush;   // an empty line after every grid
}

Cell next_cell(Cell p, char d) {
    if (d == 'R') {
        return {p.r, p.c + 1};
    }
    if (d == 'L') {
        return {p.r, p.c - 1};
    }
    if (d == 'U') {
        return {p.r - 1, p.c};
    }
    return {p.r + 1, p.c};
}

bool inside(Cell x) { return x.r >= 0 && x.r < ROWS && x.c >= 0 && x.c < COLS; }

// move robot i from its cell to cell `to`; the robot already holds the lock of `to`
void move_to(int i, Cell to) {
    Cell from;
    {
        std::lock_guard<std::mutex> g(state_m);
        from = robots[i].pos;
        robots[i].pos = to;
        robots[i].waiting = false;
        std::cout << "robot " << robots[i].name << ": (" << from.r << "," << from.c << ") -> ("
                  << to.r << "," << to.c << ")\n";
        print_grid();
    }
    cell_m[from.r][from.c].unlock();   // only now leave the old cell
}

bool same(Cell a, Cell b) { return a.r == b.r && a.c == b.c; }

// safety rule: robot i wants cell x. If the robot on x wants my cell (we want each other's cells),
// the two robots swap places. Both cells stay locked: each robot now stands on the other one's cell.
bool swap_if_head_on(int i, Cell x) {
    std::lock_guard<std::mutex> g(state_m);
    if (robots[i].swapped) {             // the other robot has already swapped both of us
        robots[i].swapped = false;
        return true;
    }
    int j = who_is_at(x);
    if (j < 0 || !robots[j].waiting || !same(robots[j].want, robots[i].pos)) {
        return false;                    // not each other's cells: wait as before
    }
    Cell mine = robots[i].pos;
    robots[i].pos = x;
    robots[j].pos = mine;
    robots[i].waiting = false;
    robots[j].waiting = false;
    robots[j].swapped = true;
    std::cout << "robots " << robots[i].name << " and " << robots[j].name << " want each other's cells: swap ("
              << mine.r << "," << mine.c << ") <-> (" << x.r << "," << x.c << ")\n";
    print_grid();
    return true;
}

// robot i goes to cell x: waits until it gets the lock of x
void go(int i, Cell x) {
    {
        std::lock_guard<std::mutex> g(state_m);
        robots[i].waiting = true;
        robots[i].want = x;
        robots[i].since = std::chrono::steady_clock::now();
    }
    while (!cell_m[x.r][x.c].try_lock()) {     // taken: wait a moment and try again
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (safety && swap_if_head_on(i, x)) {
            return;   // swapped: the robot stands on x now
        }
    }
    move_to(i, x);
}

void robot(int i) {
    cell_m[robots[i].pos.r][robots[i].pos.c].lock();   // stand on the start cell
    start->arrive_and_wait();
    size_t k = 0;   // next letter of the route
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(robots[i].step_ms));
        Cell x;
        {
            std::lock_guard<std::mutex> g(state_m);
            if (k < robots[i].route.size()) {
                x = next_cell(robots[i].pos, robots[i].route[k++]);
            } else {
                break;
            }
        }
        if (!inside(x)) {
            std::lock_guard<std::mutex> g(state_m);
            std::cout << "robot " << robots[i].name << ": the route leaves the grid, I stop\n";
            break;
        }
        go(i, x);
    }
    std::lock_guard<std::mutex> g(state_m);
    robots[i].finished = true;
    robots[i].waiting = false;
    cell_m[robots[i].pos.r][robots[i].pos.c].unlock();
    std::cout << "robot " << robots[i].name << ": finished\n";
}

// checks every 100 ms whether all robots that have not finished are stuck
void watchdog() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> g(state_m);
        auto now = std::chrono::steady_clock::now();
        bool all_done = true, all_stuck = true;
        for (auto &rb : robots) {
            if (rb.finished) {
                continue;
            }
            all_done = false;
            if (!rb.waiting || now - rb.since < std::chrono::milliseconds(STUCK_MS)) {
                all_stuck = false;
            }
        }
        if (all_done) {
            return;
        }
        if (all_stuck) {
            std::cout << "\nDEADLOCK: nobody can move.\n";
            for (auto &rb : robots) {
                if (rb.finished) {
                    continue;
                }
                int j = who_is_at(rb.want);
                std::cout << "  robot " << rb.name << " waits for (" << rb.want.r << "," << rb.want.c
                          << "), which robot " << (j < 0 ? '?' : robots[j].name) << " holds\n";
            }
            std::exit(1);
        }
    }
}

int main(int argc, char **argv) {
    const char *file = argc > 1 ? argv[1] : "routes.txt";
    std::ifstream in(file);
    if (!in) {
        std::cerr << "cannot open " << file << "\n";
        return 1;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ls(line);
        std::string first;
        if (!(ls >> first) || first[0] == '#') {
            continue;   // empty line or comment
        }
        if (first == "safety") {
            std::string v;
            ls >> v;
            safety = (v == "on");
            continue;
        }
        Robot rb;
        rb.name = first[0];
        if (!(ls >> rb.pos.r >> rb.pos.c >> rb.route >> rb.step_ms)) {
            std::cerr << "bad line: " << line << "\n";
            return 1;
        }
        if (!inside(rb.pos) || who_is_at(rb.pos) >= 0) {
            std::cerr << "robot " << rb.name << ": start cell outside the grid or taken\n";
            return 1;
        }
        robots.push_back(rb);
    }
    if (safety) {
        std::cout << "safety rule: on\n";
    }
    std::cout << "start:\n";
    print_grid();

    start = std::make_unique<std::latch>(robots.size());
    std::vector<std::thread> threads;
    for (size_t i = 0; i < robots.size(); i++)
        threads.emplace_back(robot, (int)i);
    std::thread w(watchdog);
    for (auto &t : threads)
        t.join();
    w.join();
    std::cout << "all robots finished\n";
}
