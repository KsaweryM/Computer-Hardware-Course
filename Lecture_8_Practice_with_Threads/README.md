# Lecture 8: Practice with Threads

Lecture 8 has no slides. It is a list of tasks to practise the concepts from Lecture 7: race conditions,
atomics, deadlock, condition variables, the producer-consumer problem and semaphores. Every task has its own
PDF (A4) with a story, the ready functions, the code and the questions.

| Folder | Task | PDF |
|---|---|---|
| [Task1](Task1/) | The ticket shop | [task](Task1/Task1.pdf) |
| [Task2](Task2/) | The discount code | [task](Task2/Task2.pdf) |
| [Task3](Task3/) | Statistics in a 5G base station | [task](Task3/Task3.pdf) |
| [Task4](Task4/) | Robots in a warehouse | [task](Task4/Task4.pdf) |
| [Task5](Task5/) | The pizzeria | [task](Task5/Task5.pdf) |
| [Task6](Task6/) | The lobby of an online game | [task](Task6/Task6.pdf) |
| [Task7](Task7/) | Threads take turns | [task](Task7/Task7.pdf) |
| [Task8](Task8/) | The video decoder | [task](Task8/Task8.pdf) |
| [Task9](Task9/) | At most 3 decoders at the same time | [task](Task9/Task9.pdf) |
| [Task10](Task10/) | The decoder with two semaphores | [task](Task10/Task10.pdf) |
| [Task11](Task11/) | The dining philosophers | [task](Task11/Task11.pdf) |

Tasks 6, 8, 9 and 11 start with an introduction to a new tool or problem: condition variables, the
producer-consumer problem, semaphores and the dining philosophers.

For those who want more: **[How to write a Makefile](Makefile_guide/Makefile_guide.pdf)**, with examples in
[Makefile_guide/examples](Makefile_guide/examples/).

## The code

Every task folder has a template, a `Makefile` and a `README.md`.
In a task folder, `make` compiles every `.cpp` file into `build/`, `make run` also runs it and `make clear`
removes `build/`.

## The PDFs

The PDFs are in the repository, next to their `.tex` files. To build them again (needs `latexmk`):

```
make            # build the PDFs whose source changed
make rebuild    # build all PDFs from scratch
```

`common.tex` is the shared preamble of all documents.
