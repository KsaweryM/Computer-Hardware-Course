# Task0: one more time

The bank from Lecture 7, step 3 (one mutex per account). Run it several times with 4 threads.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread bank.cpp -o bank
./bank
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od bank.cpp`, then `bank.exe`.
