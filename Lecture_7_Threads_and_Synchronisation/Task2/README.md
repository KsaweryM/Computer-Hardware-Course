# Task2: four threads say hello

Start 4 threads; thread `i` prints `Hello from thread i`. Fill in the `TODO` parts.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread hello4.cpp -o hello4
./hello4
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od hello4.cpp`, then `hello4.exe`.
