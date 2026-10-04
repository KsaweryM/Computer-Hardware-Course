# ISRinC: what does the compiler make of an ISR written in C?

An example for the slide "But our ISR is written in C". It compiles the ISR

```c
void IRAM_ATTR onButtonA() {
  presses++;
}
```

for RISC-V, the CPU of the ESP32-C3, and shows the machine code.

`IRAM_ATTR` is not part of C: it is a name from the ESP32 libraries (`esp_attr.h`), and here we do not use these
libraries. So `isr.c` defines it itself: `__attribute__((section(".iram1")))`. It only says **where** to put the
function in memory. It does not change the instructions.

## You need a cross compiler

The `gcc` on your laptop makes code for **your** CPU (x86-64 or ARM). For the ESP32-C3 we need a compiler that runs
on the laptop but makes code for **RISC-V**: a *cross compiler*.

- **The one from the Arduino core** (used by default): `riscv32-esp-elf-gcc`. It comes with
  `arduino-cli core install esp32:esp32`, the same compiler that builds our Wokwi projects. The `Makefile` finds it in
  `~/.arduino15/packages/esp32/tools/esp-rv32/`.
- **Any other RISC-V gcc**, for example `riscv64-unknown-elf-gcc` (on Ubuntu: the package `gcc-riscv64-unknown-elf`).
  It can make 32-bit code too: `make CC=riscv64-unknown-elf-gcc`. (Not tested with this example.)

## Run it

```
make          # compile and link, and show the code with real addresses (as on the slide)
make asm      # show the assembly before linking
make clean    # remove the results
```

## What to expect

`make` links the function so that the ISR is at `0x0200` and `presses` at `0x1004`, as on the slides
"Inside the CPU":

```
00000200 <onButtonA>:
 200:	00001737          	lui	a4,0x1
 204:	00472783          	lw	a5,4(a4) # 1004 <presses>
 208:	0785                	addi	a5,a5,1
 20a:	00f72223          	sw	a5,4(a4)
 20e:	8082                	ret
```

- `a4` and `a5` change, and nobody saves them: no `sw` to the stack.
- It ends with `ret`, a normal return, not `mret`.
- `lui a4, 0x1` gives `a4 = 0x1000`, and `4(a4)` is `0x1000 + 4 = 0x1004`: the address of `presses`.
  This is the `la` from the slides "Inside the CPU", split in two.
- `addi` takes only 2 bytes (`0785`): the ESP32-C3 has *compressed* instructions. That is why `sw` is at `0x20a`.

`make asm` shows the code **before** linking. The compiler does not know yet where `presses` will be in memory,
so it writes `%hi(presses)` (the upper 20 bits of the address) and `%lo(presses)` (the lower 12 bits). The linker
puts in the real numbers later.

The Arduino core compiles with `-Os`: the result is exactly the same as with `-O2`.
With `-O0` the function saves `ra` and `s0` on the stack, but still **not** `a4` and `a5`.
