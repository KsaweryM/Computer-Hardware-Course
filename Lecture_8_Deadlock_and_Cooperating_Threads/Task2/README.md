# Task2: fix the philosophers and the bank

Fix both programs: the philosophers (with the pause) and the bank (step 3), so that they can never hang.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread philosophers.cpp -o philosophers
./philosophers
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od philosophers.cpp`, then `philosophers.exe`.
