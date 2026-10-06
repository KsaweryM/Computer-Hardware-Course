# Task4: who waits for whom?

Three offices, three workers in each, three machines. Each office is one function: `office_a()`,
`office_b()`, `office_c()`. To choose the office, set `OFFICE` in `main()` to `'A'`, `'B'` or `'C'`.
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
