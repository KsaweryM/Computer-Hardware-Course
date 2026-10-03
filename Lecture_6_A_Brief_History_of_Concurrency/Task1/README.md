# Task 1: count the presses

The template for Task 1 of Lecture 6. The circuit is the same as in Lecture 5 (the project **Circuit**):
an ESP32-C3 with button A on GPIO 5, button B on GPIO 6, an LED on GPIO 4 and a 16×2 LCD on I2C.

To open it in Wokwi:

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Replace the contents of `sketch.ino` and `diagram.json` with the files from this folder.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**
   (or create a file `libraries.txt` with the contents of the one here).
4. Fill in the `TODO` parts of `sketch.ino` and click **Run**.
