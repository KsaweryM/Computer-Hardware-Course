# Lecture 8: Practice with Threads

Lecture 8 has no slides. It is a list of tasks to practise the concepts from Lecture 7: race conditions,
atomics, deadlock, condition variables, the producer-consumer problem and semaphores. All tasks are in one PDF,
**[Tasks.pdf](Tasks.pdf)**: every task has a story, the ready functions, the code and the questions.

| Folder | Task | Page in Tasks.pdf |
|---|---|---|
| [Task1](Task1/) | The ticket shop | 2 |
| [Task2](Task2/) | The discount code | 5 |
| [Task3](Task3/) | Statistics in a 5G base station | 7 |
| [Task4](Task4/) | Robots in a warehouse | 10 |
| [Task5](Task5/) | The pizzeria | 13 |
| [Task6](Task6/) | The lobby of an online game | 16 |
| [Task7](Task7/) | Threads take turns | 19 |
| [Task8](Task8/) | The video decoder | 21 |
| [Task9](Task9/) | At most 3 decoders at the same time | 25 |
| [Task10](Task10/) | The decoder with two semaphores | 28 |
| [Task11](Task11/) | The dining philosophers | 31 |

Tasks 6, 8, 9 and 11 start with an introduction to a new tool or problem: condition variables, the
producer-consumer problem, semaphores and the dining philosophers.

For those who want more: **[How to write a Makefile](Makefile_guide/Makefile_guide.pdf)**, with examples in
[Makefile_guide/examples](Makefile_guide/examples/).

## The code

Every task folder has a template, a `Makefile` and a `README.md`.
In a task folder, `make` compiles every `.cpp` file into `build/`, `make run` also runs it and `make clear`
removes `build/`.

## The PDFs

The PDFs are in the repository, next to their `.tex` files. `Tasks.tex` puts the text of every task
(`TaskK/TaskK.tex`) into one PDF. To build them again (needs `latexmk`):

```
make            # build the PDFs whose source changed
make rebuild    # build all PDFs from scratch
```

`common.tex` is the shared preamble of all documents.
