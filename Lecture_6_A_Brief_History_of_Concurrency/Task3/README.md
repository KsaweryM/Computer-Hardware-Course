# Task3: program the robot

The template for Task 3 of Lecture 6. The robot: two wheels (stepper motors), a distance sensor (HC-SR04), a buzzer
and the LCD. All the wires are ready. The functions for the parts are ready too, in `robot.cpp` (the list is in `robot.h`
and at the top of `Task3.ino`): `setupRobot()`, `measureCm()`, `showDistance()`, `beep()`, `forward()` and `stop()`. So is the task `watch`: every 100 ms it measures the distance and prints it in the
**Serial Monitor**. Add the tasks `show`, `drive` and `warn`: see the steps at the top of `Task3.ino`.

The circuit:

- the HC-SR04: TRIG on GPIO 0, ECHO on GPIO 1,
- the wheels: two A4988 drivers, both with STEP on GPIO 4 and DIR on GPIO 5, so both wheels turn together,
- the buzzer on GPIO 10,
- the LCD on GPIO 8 and 9 (as in Task 2).

To change the distance: start the simulation, click the sensor and move the slider.

## In VS Code (Wokwi extension)

1. Install [`arduino-cli`](https://arduino.github.io/arduino-cli/), the ESP32 core and the library:
   `arduino-cli core install esp32:esp32` and `arduino-cli lib install "LiquidCrystal I2C"`.
2. Open **this folder** in VS Code (File → Open Folder): `wokwi.toml` must be at the top of the workspace.
3. Compile: `make` (the firmware goes to `build/`). Compile again after every change.
4. Run **Wokwi: Start Simulator** from the command palette.

## In the browser (wokwi.com)

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Paste `Task3.ino` into `sketch.ino`, and `diagram.json` into `diagram.json`. Add two new files (the arrow next to
   the file tabs, **New file...**): `robot.h` and `robot.cpp`, and paste their contents.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**.
4. Click **Run**.
