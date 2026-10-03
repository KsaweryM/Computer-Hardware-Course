# Task5: atomic, and a better idea

Two more versions of the counter: an atomic one and a local sum. Measure the time of each.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread counter.cpp -o counter
./counter
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od counter.cpp`, then `counter.exe`.
