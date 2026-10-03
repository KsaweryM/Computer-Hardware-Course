# Circuit: the Wokwi project from Lecture 5

The circuit used in Lecture 6: an ESP32-C3 with an LED on GPIO 4, button A on GPIO 5,
button B on GPIO 6 and a 16×2 LCD on I2C (SDA = GPIO 8, SCL = GPIO 9).

To open it in Wokwi:

1. Go to [wokwi.com](https://wokwi.com), choose **ESP32**, then **ESP32-C3** under Starter Templates.
2. Replace the contents of `sketch.ino` and `diagram.json` with the files from this folder.
3. Add the library: open the **Library Manager** tab and add **LiquidCrystal I2C**
   (or create a file `libraries.txt` with the contents of the one here).
4. Click **Run**. The LCD shows `A:1 B:1`; press a button and its value changes to 0.
