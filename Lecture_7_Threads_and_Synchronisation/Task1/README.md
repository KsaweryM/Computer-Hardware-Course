# Task1: how many cores?

How many threads can your laptop run at the same moment?

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread cores.cpp -o cores
./cores
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od cores.cpp`, then `cores.exe`.
