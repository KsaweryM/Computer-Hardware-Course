# Task6: the lunch bell

Three workers wait for the lunch bell. After 2 s the boss rings it, and all of them go to lunch.
`bell.cpp` waits in a loop (busy waiting). Replace it with a `std::condition_variable`.
The ready functions are in `bell.h` (we do not look inside).

Measure the time with `time ./build/bell` (Linux, macOS).

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread bell.cpp -o bell
./bell
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od bell.cpp`, then `bell.exe`.
