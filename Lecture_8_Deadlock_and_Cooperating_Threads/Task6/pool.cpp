// pool.cpp: a thread pool. Write work() and the destructor. Compile with -O2.
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <chrono>

class ThreadPool {
public:
    explicit ThreadPool(int n) {
        for (int i = 0; i < n; i++)
            workers.emplace_back([this] { work(); });
    }
    void submit(std::function<void()> task) {
        { std::lock_guard<std::mutex> lock(m);
          tasks.push(task); }
        cv.notify_one();
    }
    ~ThreadPool();
private:
    void work();
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex m;
    std::condition_variable cv;
    bool stop = false;
};

// TODO 1: wait for a task or for stop; take the task, unlock, run it. Repeat.
void ThreadPool::work() {
}

// TODO 2: set stop, wake up all workers, join them.
ThreadPool::~ThreadPool() {
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; (long long)d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}

int main(int argc, char **argv) {
    // the number of workers: ./pool 4  (default: hardware_concurrency)
    const int WORKERS = argc > 1 ? std::atoi(argv[1]) : (int)std::thread::hardware_concurrency();
    const int LIMIT = 5'000'000, CHUNK = 100'000;
    std::atomic<int> primes{0};
    auto start = std::chrono::steady_clock::now();
    {
        ThreadPool pool(WORKERS);
        for (int start = 0; start < LIMIT; start += CHUNK)
            pool.submit([start, &primes] {
                int c = 0;
                for (int n = start; n < start + CHUNK; n++)
                    if (isPrime(n)) c++;
                primes += c;
            });
    }   // the destructor waits for all tasks
    std::chrono::duration<double, std::milli> ms = std::chrono::steady_clock::now() - start;
    std::cout << WORKERS << " workers: " << primes << " primes (expected 348513), "
              << ms.count() << " ms\n";
}
