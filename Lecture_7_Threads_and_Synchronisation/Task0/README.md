# Task0: C++ on your laptop

Check that you can compile and run a C++ program with a thread.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread hello.cpp -o hello
./hello
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od hello.cpp`, then `hello.exe`.
