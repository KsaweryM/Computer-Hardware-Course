// Task 1: count the presses of button A with an interrupt.
// The circuit: button A on GPIO 5, button B on GPIO 6, the LCD on I2C (SDA = GPIO 8, SCL = GPIO 9).
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_A = 5;
volatile int presses = 0;      // shared by the ISR and loop(), so it is volatile

// TODO 1: write the ISR. It only adds 1 to presses.
//         Do not forget IRAM_ATTR.


void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 2: set BUTTON_A as an input with the pull-up resistor (INPUT_PULLUP),
  //         and attach your ISR to it with attachInterrupt(..., FALLING).

}

void loop() {
  // TODO 3: show "Presses: N" in row 0 of the LCD.

  // TODO 4 (question 3): add delay(2000) here. Do you lose any presses now?
}
