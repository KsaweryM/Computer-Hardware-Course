# Task2: three LEDs

The template for Task 2 of Lecture 6: three LEDs that change every 300, 500 and 700 ms, with one timer interrupt
(a tick every 100 ms). Fill in the `TODO` parts of `Task2.ino`, run it, and compare with Simulator 2.

The circuit: the circuit from Lecture 5 with two more LEDs: LED 1 on GPIO 4, LED 2 on GPIO 7, LED 3 on GPIO 3. The buttons and
the LCD are still in the circuit, but this task does not use them.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`). Compile again after every change.
4. Run **Wokwi: Start Simulator** from the command palette.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `Task2.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Click **Run**.
