# Compiles isr.c for RISC-V (the CPU of the ESP32-C3) and shows the machine code.
#   make          compile and link, and show the code with real addresses (as on the slide)
#   make asm      show the assembly before linking (with %hi and %lo)
#   make clean    remove the results
# It needs a cross compiler for RISC-V. By default it uses riscv32-esp-elf-gcc from the Arduino core
# (installed with arduino-cli). Another one:  make CC=riscv64-unknown-elf-gcc
ESP_GCC := $(lastword $(sort $(wildcard $(HOME)/.arduino15/packages/esp32/tools/esp-rv32/*/bin/riscv32-esp-elf-gcc)))
ifeq ($(origin CC),default)
  CC := $(if $(ESP_GCC),$(ESP_GCC),riscv32-esp-elf-gcc)
endif
OBJDUMP := $(subst gcc,objdump,$(CC))
# the CPU of the ESP32-C3 and the same optimisation as on the slide
CFLAGS  := -O2 -march=rv32imc_zicsr -mabi=ilp32
# link only this function: the ISR at 0x0200 and presses at 0x1004, as on the slides "Inside the CPU"
LDFLAGS := -nostdlib -nostartfiles -Wl,--no-relax -Wl,-e,onButtonA \
           -Wl,--section-start=.iram1=0x0200 -Wl,--section-start=.sbss=0x1004

.PHONY: all asm clean

all: isr.elf
	@echo "== after linking: $(notdir $(CC)) $(CFLAGS)"
	@$(OBJDUMP) -d $< | sed -n '/<onButtonA>:/,/ret/p'

isr.elf: isr.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

asm: isr.s
	@echo "== before linking: $(notdir $(CC)) $(CFLAGS)"
	@grep -v '^\s*\.\(file\|attribute\|globl\|type\|size\|ident\|option\|align\|p2align\)' isr.s

isr.s: isr.c
	$(CC) $(CFLAGS) -S $< -o $@

clean:
	rm -f isr.s isr.elf
