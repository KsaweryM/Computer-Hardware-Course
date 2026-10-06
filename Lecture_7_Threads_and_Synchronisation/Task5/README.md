# Task5: fix office A

`office3.cpp` is office A from Task 4: it can hang. Fix it in two ways: with one order of the locks
(change only `main()`) and with `std::scoped_lock` (change only `worker()`).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread office3.cpp -o office3
./office3
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od office3.cpp`, then `office3.exe`.
