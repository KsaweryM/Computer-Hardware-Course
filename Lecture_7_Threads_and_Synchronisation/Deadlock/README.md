# Deadlock: two workers, two locks

`lunch()` takes the fridge, then the microwave; `soup()` takes them in the other order.
Run it a few times: does it print `all done`? A program that hangs can be stopped with Ctrl+C.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread deadlock.cpp -o deadlock
./deadlock
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od deadlock.cpp`, then `deadlock.exe`.
