# Project1: the auditor (mini-project 1)

The bank of step 4 (the lock order), plus an auditor thread that checks the sum every 100 ms while the transfers run. It must lock all accounts without a deadlock. Fill in `auditor()`.

## Compile and run

With `make` (Linux, macOS, MinGW on Windows):

```
make            # compile into build/
make run        # compile and run
```

Or by hand:

```
g++ -std=c++20 -O0 -pthread auditor.cpp -o auditor
./auditor
```

With MSVC (Developer Command Prompt): `cl /std:c++20 /EHsc /Od auditor.cpp`, then `auditor.exe`.
