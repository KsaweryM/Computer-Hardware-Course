# Computer Hardware Course

[![CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

A hands-on course on **how a processor is built and how software talks to hardware**.

The course starts with the building blocks of a CPU and **assembly programming**, first on the
simple teaching machine **MARIE** and then on a real instruction set, **RISC-V**. It shows what
makes modern processors fast (**pipelining** and the **cache**), moves to a real microcontroller,
the **ESP32-C3**, to talk to other devices, and ends with concurrency: interrupts, schedulers and
threads.

- **Lecture 1** builds a computer from scratch: what a computer has to do, the design decisions
  behind the von Neumann model, and how a CPU works inside (registers, ALU, control unit and the
  fetch-decode-execute cycle). It ends with the first **assembly programs in MARIE**: input and
  output, jumps and loops.
- **Lecture 2** looks closer at the processor: **addressing modes** (direct, indirect, immediate)
  and arrays in MARIE, how the CPU talks to memory through MAR, MBR and the bus, how the
  **control unit** generates its signals (hardwired or microprogrammed), and the **RISC vs. CISC**
  debate.
- **Lecture 3** asks what "fast" means: execution time, CPI, the iron law of performance, the
  megahertz myth and benchmarks. It then moves from MARIE to **RISC-V** in the Ripes simulator
  and shows how a **pipeline** runs several instructions at once, and what branches do to it.
- **Lecture 4** hits the **memory wall**: why memory cannot be both fast and cheap, how
  **locality** makes a cache work, lines and tags, direct-mapped and set-associative caches,
  hits, misses and AMAT, measured in Ripes and on your own laptop.
- **Lecture 5** moves to the **ESP32-C3** (simulated in Wokwi). We connect LEDs, buttons and an
  LCD, learn how the processor talks to other devices through **GPIO** and the **I2C** bus, and
  control the GPIO controller **directly through its registers** (memory-mapped I/O) instead of
  library calls. It ends with **polling** and why it misses events and wastes the CPU.
- **Lecture 6** replaces polling with **interrupts** (from a button and a timer), shows how a
  **scheduler** lets one processor run several tasks with time slices and context switches, and
  runs a real scheduler, **FreeRTOS**, on the ESP32-C3.
- **Lecture 7** moves to **threads in C++** on a multi-core laptop: why `counter++` loses updates
  (a race condition, seen down to the `lw`/`addi`/`sw` instructions), and how to fix it with
  **mutexes** and **atomics**, and what each fix costs.
- **Lecture 8** explains why the bank program from Lecture 7 stops: **deadlock**, its four
  conditions and the dining philosophers. It fixes it with a lock order and `std::scoped_lock`,
  then shows how threads can **cooperate** without busy waiting: condition variables, semaphores,
  the producer-consumer pattern and a thread pool.

Author: **Ksawery Możdżyński**

---

## Course Structure

The course is divided into eight lectures:

| # | Title | Topics |
|---|-------|--------|
| **1** | Introduction to Processor Architecture | How a CPU is built (memory, registers, ALU, control unit), the fetch-decode-execute cycle, first assembly programs in MARIE: input/output, jumps and loops |
| **2** | Inside the Processor | Addressing modes, MAR/MBR and the bus, the von Neumann bottleneck, the control unit (hardwired vs. microprogrammed), RISC vs. CISC |
| **3** | Performance and Pipelining | CPI, clock rate and the megahertz myth, MIPS, benchmarks, from MARIE to RISC-V (Ripes), the five-stage pipeline, branches and speculation |
| **4** | Memory and Cache | The memory wall, the memory hierarchy, locality, direct-mapped and set-associative caches, line/tag, hit rate, AMAT |
| **5** | Input/Output: Devices and Polling | ESP32-C3 in Wokwi, LEDs and buttons on GPIO, an LCD on the I2C bus, memory-mapped I/O, controlling the GPIO controller through its registers, polling and its limits |
| **6** | A Brief History of Concurrency: From a Button to a Scheduler | Interrupts and ISRs, timer interrupts, time slices, context switches, task states and priorities, FreeRTOS on the ESP32-C3 |
| **7** | Threads and Synchronisation in C++ | Threads, race conditions and data races, critical sections, mutexes, atomics, lock granularity |
| **8** | Deadlock and Cooperating Threads | Deadlock and its four conditions, dining philosophers, lock ordering, busy waiting, condition variables, semaphores, producer-consumer, thread pools |

---

## Simulators

All interactive simulators created for this course are collected on one page:
**[ksawerym.github.io/ComputerHardwareSimulators](https://ksawerym.github.io/ComputerHardwareSimulators/)**. They run in the browser, in Polish and English,
nothing to install. Direct links to each topic:

| Lecture | Simulators |
|---------|------------|
| 3 | [RISC-V pipeline](https://ksawerym.github.io/ComputerHardwareSimulators/#pipeline): stalls, forwarding and flushes, cycle by cycle |
| 4 | [Direct-mapped cache](https://ksawerym.github.io/ComputerHardwareSimulators/#cache): blocks, lines, tags, hits and misses |
| 5 | [I2C](https://ksawerym.github.io/ComputerHardwareSimulators/#io-i2c), [device registers](https://ksawerym.github.io/ComputerHardwareSimulators/#io-mmio), [GPIO controller](https://ksawerym.github.io/ComputerHardwareSimulators/#io-gpio) |
| 6 | [Polling vs interrupt](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-poll), [an interrupt](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-intr), [interrupt step by step](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-irq), [timer and tick](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-tick), [time slice](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-slice), [context switch](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-ctx), [states and priorities](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-states), [shared counter](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-shared) |
| 7 | [Race step by step](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-race), [mutex](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-mutex) |
| 8 | [Deadlock](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-dead), [producer-consumer](https://ksawerym.github.io/ComputerHardwareSimulators/#cc-pc) |

The course also uses these tools:

- [**MARIE.js**](https://marie.js.org): a simple teaching CPU for the first assembly programs
- [**Ripes**](https://ripes.dk): a RISC-V processor simulator with pipeline and cache views, in the browser
- [**Wokwi**](https://wokwi.com): an online simulator of the ESP32-C3 with LEDs, buttons and an LCD
- [**Compiler Explorer**](https://godbolt.org): to see the assembly that the compiler produces from C++

---

## Pre-built PDFs

Ready-to-use presentation slides are available in the [`builded_presentation/`](builded_presentation/) folder:

- [Lecture 1: Introduction to Processor Architecture](builded_presentation/Lecture_1_Introduction_to_Processor_Architecture.pdf)
- [Lecture 2: Inside the Processor](builded_presentation/Lecture_2_Inside_the_Processor.pdf)
- [Lecture 3: Performance and Pipelining](builded_presentation/Lecture_3_Performance_and_Pipelining.pdf)
- [Lecture 4: Memory and Cache](builded_presentation/Lecture_4_Memory_and_Cache.pdf)
- [Lecture 5: Input/Output: Devices and Polling](builded_presentation/Lecture_5_Input_Output_Devices_and_Polling.pdf)
- [Lecture 6: A Brief History of Concurrency](builded_presentation/Lecture_6_A_Brief_History_of_Concurrency.pdf)
- [Lecture 7: Threads and Synchronisation in C++](builded_presentation/Lecture_7_Threads_and_Synchronisation.pdf)
- [Lecture 8: Deadlock and Cooperating Threads](builded_presentation/Lecture_8_Deadlock_and_Cooperating_Threads.pdf)

---

## Tasks

The starter files of the tasks are in the folder of each lecture, one folder per task
(for example [`Lecture_7_Threads_and_Synchronisation/Task3`](Lecture_7_Threads_and_Synchronisation/Task3/)).
Every folder has a `Makefile` and a `README.md` with the instructions:

- **Lecture 6** (ESP32-C3 in Wokwi): `Circuit` (the circuit from Lecture 5) and `Task1` to `Task5`.
  Each one is a Wokwi project for the VS Code extension: `make` compiles it with `arduino-cli`,
  then **Wokwi: Start Simulator** runs it.
- **Lectures 7 and 8** (C++ on your laptop): `make` compiles every `.cpp` file into `build/`, `make run` also runs them.

---

## Building the presentations yourself

Requirements:
- `latexmk`
- A full TeX distribution (TeX Live / MiKTeX) with Beamer and the usual packages (`tikz`, `fontawesome5`, `listings`, etc.)

```bash
# Build everything
make

# Build a single lecture, by its number or directory name
make 4
make Lecture_4_Memory_and_Cache

# Build one lecture from scratch, even if nothing changed
make rebuild-4

# List the available lectures
make list

# Clean auxiliary files and PDFs
make clean
```

The Makefile automatically places the resulting PDFs in `builded_presentation/`.

To keep the PDFs up to date automatically, turn on the pre-commit hook once:

```bash
git config core.hooksPath .githooks
```

Then every commit that changes a `Lecture_*/main.tex` rebuilds the changed presentations
and adds the new PDFs to the same commit (skip it once with `git commit --no-verify`).

---

## Who is this for?

- Students taking their first course on computer architecture or operating systems
- Programmers who want to understand what happens below their code: registers, caches, interrupts, threads
- Teachers looking for ready-made, hands-on slides with exercises and solutions

No prior hardware knowledge is assumed. The course builds everything step by step,
starting from a computer you can program by hand.

---

## License

© Ksawery Możdżyński. The slides, their LaTeX sources and the PDFs in this repository are licensed under the
[Creative Commons Attribution 4.0 International License (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/).

You are free to use, share and adapt the material for any purpose, including teaching and commercial use,
as long as you give appropriate credit, provide a link to the license and indicate if changes were made.
A suggested attribution:

> "Computer Hardware Course" by Ksawery Możdżyński,
> https://github.com/KsaweryM/Computer-Hardware-Course, licensed under CC BY 4.0.

If you find the course useful, a star ⭐ is always appreciated!
