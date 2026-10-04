// Task 1: count the presses of button A with an interrupt.
// Write the code for points 1 to 3 in place of the TODO lines.
// 1. Write the ISR of button A: it adds 1 to presses. In setup(), attach it to button A with attachInterrupt.
// 2. In loop(), show the number on the LCD: "Presses: N".
// 3. Write a second ISR for button B (GPIO 6): it sets presses back to 0. Attach it to button B.
// 4. Add delay(2000) to loop(). Do you still lose any presses? Why not?
// The circuit: button A on GPIO 5, button B on GPIO 6, the LCD on I2C (SDA = GPIO 8, SCL = GPIO 9).
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_A = 5, BUTTON_B = 6;
volatile int presses = 0;      // shared by the ISRs and loop(), so it is volatile

// TODO 1: the ISR of button A. It only adds 1 to presses. Do not forget IRAM_ATTR.

// TODO 3: the ISR of button B. It sets presses back to 0.


void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 1: set BUTTON_A as an input with the pull-up resistor (INPUT_PULLUP),
  //         and attach its ISR with attachInterrupt(..., FALLING).

  // TODO 3: the same for BUTTON_B.

}

void loop() {
  // TODO 2: show "Presses: N" in row 0 of the LCD.

  // TODO 4: add delay(2000) here. Do you lose any presses now?
}
