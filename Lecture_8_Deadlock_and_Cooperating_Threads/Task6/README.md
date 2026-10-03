# Task6: count primes with a pool

A thread pool counts the primes below 5 000 000. Write `work()` and the destructor. Run it as `./build/pool 1`, `./build/pool 2`, `./build/pool 4`.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O2 -pthread pool.cpp -o pool
./pool
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /O2 pool.cpp`, then `pool.exe`.
