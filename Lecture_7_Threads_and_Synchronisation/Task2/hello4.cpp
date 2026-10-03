// Task 2: four threads say hello.
// 1. Run it 5 times. Is the order of the lines always the same?
// 2. Do you ever see two messages mixed in one line?
// 3. Remove the loop with join(). What happens?
#include <iostream>
#include <thread>
#include <vector>

void hello(int i) {
    // TODO 1: print "Hello from thread i"
}

int main() {
    std::vector<std::thread> threads;

    // TODO 2: start 4 threads, thread i runs hello(i)

    // TODO 3: join all threads
}
