# Project2: a pipeline (mini-project 2)

Three threads connected by two bounded buffers: generate the numbers 1 to 1000, square them, add them up. Fill in the `TODO` parts. Expected sum: 333833500.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread pipeline.cpp -o pipeline
./pipeline
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od pipeline.cpp`, then `pipeline.exe`.
