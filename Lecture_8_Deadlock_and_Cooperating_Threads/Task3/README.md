# Task3: three ways to wait

Version 1 (busy waiting) is ready. Write version 2 (sleep and check) and version 3 (a condition variable).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread waiting.cpp -o waiting
./waiting
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od waiting.cpp`, then `waiting.exe`.
