# Task4: who waits for whom?

Three workers, three machines, two offices. Office A and office B differ only in worker 2.
To run office B, comment out the line of office A in `main()` and uncomment the line of office B.
A program that hangs can be stopped with Ctrl+C.

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
