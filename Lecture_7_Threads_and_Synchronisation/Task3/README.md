# Task3: an order for 1000 engines

Three lines build exactly 1000 engines, each with its own serial number. Write `line()` in
`factory.cpp` with `std::atomic`, no mutex. The ready functions are in `factory.h` (we do not look inside).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread factory.cpp -o factory
./factory
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od factory.cpp`, then `factory.exe`.
