# Task4: the bounded buffer

The producer is ready. Write `consumer()`.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread buffer.cpp -o buffer
./buffer
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od buffer.cpp`, then `buffer.exe`.
