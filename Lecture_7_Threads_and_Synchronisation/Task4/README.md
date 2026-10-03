# Task4: fix it with a mutex, and measure

Start from the counter of Task 3. Fill in the `TODO` parts.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread race_mutex.cpp -o race_mutex
./race_mutex
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od race_mutex.cpp`, then `race_mutex.exe`.
