# Task3: who runs loop()?

The code for Task 3 of Lecture 6. Run it and read the answer in the **Serial Monitor**.

The circuit: an ESP32-C3 with an LED on GPIO 4, button A on GPIO 5, button B on GPIO 6 and a 16×2 LCD on I2C (SDA = GPIO 8, SCL = GPIO 9).

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`). Compile again after every change.
4. Run **Wokwi: Start Simulator** from the command palette.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `Task3.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Click **Run**.
