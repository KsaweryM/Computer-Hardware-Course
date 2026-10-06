# Task1: the office fridge

Three workers share one office fridge. A cleaner checks that it is not overfull.
Write `worker()`, `cleaner()` and `main()` in place of the TODO lines in `fridge.cpp`.
The ready functions are in `office.h` (we do not look inside).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread fridge.cpp -o fridge
./fridge
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od fridge.cpp`, then `fridge.exe`.
