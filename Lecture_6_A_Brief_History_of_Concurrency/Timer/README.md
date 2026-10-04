# Timer: a timer interrupt blinks the LED

The example for the slide "Try it: a timer blinks the LED" of Lecture 6. It is the code from the slides
"A timer in the code": a hardware timer calls the ISR `onTimer` every 500 ms, and the ISR switches the LED.
`loop()` is empty.

The circuit: the same as the project **Circuit** (only the LED on GPIO 4 is used).

1. Does the LED change every 500 ms?
2. Change `500000` to `100000`. What happens?
3. `loop()` is empty. Who switches the LED?

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `Timer.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C** (the LCD of the circuit).
4. Click **Run**.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`). Compile again after every change.
4. Run **Wokwi: Start Simulator** from the command palette.
