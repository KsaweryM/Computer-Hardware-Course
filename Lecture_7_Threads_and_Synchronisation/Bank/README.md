# Bank: the bank

Random transfers between 10 accounts. Step 1 has no synchronisation; steps 2 and 3 are on the slides.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread bank.cpp -o bank
./bank
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od bank.cpp`, then `bank.exe`.
