# Factory: three lines, one counter

The engine factory from the lecture, in three versions: without protection (`factory.cpp`),
with a mutex (`factory_mutex.cpp`) and with `std::atomic` (`factory_atomic.cpp`). Compile with `-O0`
and run each version a few times. To compare the speed, change `1000000` to `10000000` and run it with `time`.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread factory.cpp -o factory
./factory
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od factory.cpp`, then `factory.exe`.
