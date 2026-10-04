# ISRRule3: an ISR and `loop()` change one variable

An experiment for the slides "Rules for an ISR: 3. share data carefully". `loop()` counts all presses so far:

```cpp
counted += presses;   // take the new presses
presses = 0;          // start again from 0
```

In theory no press is lost. But if the ISR adds 1 between these two lines, `presses = 0` wipes it out: the press
is lost, even on one core, even with `volatile`.

A person cannot press a button exactly between two instructions. So here a **timer** makes the "presses": its ISR
runs 10 000 times per second, exactly like the ISR of a button (`presses++`). A second counter, `made`, is changed
**only** by the ISR: it says how many presses there really were. Every second the sketch stops the timer for a
moment, compares `made` with what `loop()` counted, and shows the difference.

## What to expect

On the LCD and in the Serial Monitor, once per second, for example after 3 seconds:

```
made: 30000
lost: ...
```

Both numbers are never reset, they only grow: `made` by about 10 000 every second, `lost` by the presses that
came between the two lines. `lost` should grow every second, by a different amount each time.
We have not run it yet, so we do not give a number here.

The counters are `unsigned long` (32 bits). After 4 294 967 295 they wrap around to 0 by themselves, after about
5 days. `made - counted` stays correct even then, because unsigned arithmetic wraps around in the same way.

## Where exactly is the gap?

The real code of `loop()` (`riscv32-esp-elf-objdump -d build/ISRRule3.ino.elf`, the compiler of the Arduino core
3.3.12 with its default `-Os`):

```
lw   a4,544(s0)     # read presses
...                 # 7 other instructions: the rest of counted += presses, saving registers
sw   zero,544(s0)   # presses = 0
```

The compiler put 7 other instructions between the read and the reset. An interrupt after any of these 8
instructions loses a press.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `ISRRule3.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Click **Run**. The result is on the LCD and in the Serial Monitor.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`).
4. Run **Wokwi: Start Simulator** from the command palette.

How to fix it without losing presses: on Tuesday.
