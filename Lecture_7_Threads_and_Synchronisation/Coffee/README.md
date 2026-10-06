# Coffee: wait until the coffee is ready

The coffee example from the lecture, in two versions: the worker looks again and again (`coffee.cpp`,
busy waiting) and the worker sleeps until the machine calls it (`coffee_cv.cpp`, a `std::condition_variable`).
Run both with `time` (Linux, macOS) and compare `user`.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread coffee_cv.cpp -o coffee_cv
time ./coffee_cv
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od coffee_cv.cpp`, then `coffee_cv.exe`.
