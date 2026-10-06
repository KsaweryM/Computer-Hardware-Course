# Task2: lock the fridge

`fridge.cpp` is the program from Task 1. Add a mutex, so that the fridge is never overfull.
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
