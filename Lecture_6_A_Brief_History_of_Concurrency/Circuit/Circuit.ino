// Circuit: the project from Lecture 5 (Task 4), the starting point for Lecture 6.
// The LCD shows the state of both buttons: 1 = not pressed, 0 = pressed.
#include <Wire.h>               // the I2C bus: talks to devices over 2 wires (SDA, SCL)
#include <LiquidCrystal_I2C.h>  // ready-made functions for an LCD connected over I2C

#define LED   4                 // the LED is on GPIO 4 (not used in this task)
#define BTN_A 5                 // button A is on GPIO 5
#define BTN_B 6                 // button B is on GPIO 6

// The LCD: I2C address 0x27, 16 columns, 2 rows.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED, OUTPUT);         // the LED pin is an output: the program sets it
  pinMode(BTN_A, INPUT_PULLUP); // button A: reads 1 when not pressed, 0 when pressed
  pinMode(BTN_B, INPUT_PULLUP); // button B: the same
  Wire.begin(8, 9);             // start the I2C bus: SDA on GPIO 8, SCL on GPIO 9
  lcd.init();                   // prepare the LCD (sends its start-up commands over I2C)
  lcd.backlight();              // switch on the backlight, so the text is visible
}

void loop() {
  lcd.setCursor(0, 0);          // move the cursor to column 0, row 0 (top left)
  lcd.print("A:");              // the label for button A
  lcd.print(digitalRead(BTN_A));// the state of button A: 1 or 0
  lcd.print(" B:");             // the label for button B
  lcd.print(digitalRead(BTN_B));// the state of button B: 1 or 0
  delay(100);                   // wait 100 ms, so the LCD is not redrawn all the time
}
