# ISRRule2: what does `delay()` really do inside an ISR?

An experiment for the slide "Rules for an ISR: 2. some things are not allowed". The slide says:
`delay()` in an ISR puts to sleep the program that was interrupted, and does not wait at all.

- Button A (GPIO 5): its ISR calls `delay(1000)`.
- Button B (GPIO 6): its ISR does not call `delay()`. For comparison.

For each press the sketch shows, on the LCD and in the Serial Monitor, how long the ISR itself took, and how long
`loop()` was stopped around the press. `loop()` never waits: it only reads `micros()` as fast as it can, so a long
time between two of its rounds means that it was stopped.

## What to expect

On the LCD, after a press of A, something like this (expected from the run with 100 ms below):

```
ISR A: 17 us
loop(): 999 ms
```

The ISR of button A takes only microseconds, although it calls `delay(1000)`. Instead `loop()` stops for
about 1 second. `delay()` did not make the ISR wait: it put to sleep the task that runs `loop()`.
Button B shows a few microseconds and 0 ms.

Measured in Wokwi with `delay(100)`: the ISR took 17 us, `loop()` was stopped for 99.2 to 100.0 ms.

**Wait until the LCD shows the result before you press A again.** While `loop()` sleeps, the IDLE task runs.
A press in that second interrupts the IDLE task, and `delay()` puts **it** to sleep. The result is not
defined: one more reason why the rule is "never call a function that waits".

## Why (Arduino core 3.3.12, ESP32-C3)

- `delay(ms)` is `vTaskDelay(ms / portTICK_PERIOD_MS)` (`cores/esp32/esp32-hal-misc.c`).
- `vTaskDelay` does not check whether it runs in an ISR. It puts the **current task** on the list of delayed
  tasks. Inside an ISR, the current task is the one that was interrupted: here `loopTask`, which runs `loop()`.
- Then it calls `vPortYield`. In an ISR (`port_uxInterruptNesting != 0`) this only asks for a task switch at
  the end of the ISR (`vPortYieldFromISR`), so the ISR goes on at once.

(Checked in the disassembly of `libfreertos.a` from `esp32c3-libs/3.3.12`.)

The same can happen by chance: every 2 seconds the Arduino core lets `loopTask` sleep for 5 ms. A press of A
exactly then interrupts the IDLE task.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `ISRRule2.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Click **Run** and press the buttons. The result is on the LCD and in the Serial Monitor.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`).
4. Run **Wokwi: Start Simulator** from the command palette, and press the buttons.
