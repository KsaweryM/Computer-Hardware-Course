# Task3: Monday's counter in C++

Two threads increase one shared counter. Compile it with `-O0` and run it several times.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread race.cpp -o race
./race
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od race.cpp`, then `race.exe`.
