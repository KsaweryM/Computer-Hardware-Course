# Task5: a semaphore

A print room with 2 printers and 8 threads. Fill in the `TODO` parts.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread printers.cpp -o printers
./printers
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od printers.cpp`, then `printers.exe`.
