# Task 1: count the presses

The template for Task 1 of Lecture 6. The circuit is the same as in Lecture 5 (the project **Circuit**):
an ESP32-C3 with button A on GPIO 5, button B on GPIO 6, an LED on GPIO 4 and a 16×2 LCD on I2C.
Fill in the `TODO` parts of `Task1.ino`.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `Task1.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Fill in the `TODO` parts and click **Run**.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`). Compile again after every change.
4. Run **Wokwi: Start Simulator** from the command palette.
