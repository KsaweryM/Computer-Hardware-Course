# Task7: the warehouse

Three lines build engines, two sellers sell them, and the warehouse holds at most 10.
`warehouse.cpp` waits in a loop (busy waiting). Replace it with a `std::condition_variable`.
The ready functions are in `warehouse.h` (we do not look inside).

Measure the time with `time ./build/warehouse` (Linux, macOS).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread warehouse.cpp -o warehouse
./warehouse
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od warehouse.cpp`, then `warehouse.exe`.
