// ISRRule2: what does delay() really do inside an ISR?
// The slide "Rules for an ISR: 2. some things are not allowed" says:
//   delay() in an ISR puts to sleep the program that was interrupted, and does not wait at all.
// This sketch measures both things. Press the buttons and look at the LCD (or the Serial Monitor).
//
//   Button A (GPIO 5): its ISR calls delay(1000).
//   Button B (GPIO 6): its ISR does not call delay(). For comparison.
//
// Wait until the LCD shows the result before you press A again (see README.md).
// For each press it shows:
//   - how long the ISR itself took (micros() at its start and at its end),
//   - how long loop() was stopped around the press.
//
// Why it works this way (Arduino core 3.3.12, ESP32-C3):
//   delay(ms) is vTaskDelay(ms / portTICK_PERIOD_MS). vTaskDelay does not check whether it runs in an ISR.
//   It puts the CURRENT task to sleep: inside an ISR this is the task that was interrupted, here the task
//   that runs loop(). Then it asks for a task switch; in an ISR the switch only happens when the ISR ends.
//   So the ISR goes on at once, and loop() sleeps for 1 second.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_A = 5, BUTTON_B = 6;

volatile unsigned long pressAt = 0;     // micros() when the ISR started
volatile unsigned long isrTook = 0;     // how long the ISR took, in microseconds
volatile char pressedButton = 0;        // 'A' or 'B', 0 = no new press

void IRAM_ATTR onButtonA() {
  unsigned long start = micros();
  delay(1000);                          // NOT allowed in an ISR: what happens?
  isrTook = micros() - start;
  pressAt = start;
  pressedButton = 'A';
}

void IRAM_ATTR onButtonB() {
  unsigned long start = micros();
  // no delay() here
  isrTook = micros() - start;
  pressAt = start;
  pressedButton = 'B';
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();
  lcd.print("Press A or B");
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonA, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), onButtonB, FALLING);
  Serial.print("Press button A (delay in the ISR) or button B (no delay).\r\n");
}

unsigned long last = 0;                 // micros() in the previous round of loop()

void loop() {
  // loop() never waits: it only looks at the clock, as fast as it can.
  // If it is stopped, the time between two rounds becomes long.
  unsigned long now = micros();
  char b = pressedButton;
  if (b != 0 && last <= pressAt && pressAt <= now) {
    // this round and the previous one are on both sides of the press:
    // now - last = how long loop() was stopped around the press
    unsigned long stopped = now - last;
    pressedButton = 0;
    Serial.printf("Button %c: the ISR took %lu us, loop() was stopped for %lu us (%.1f ms)\r\n",
                  b, isrTook, stopped, stopped / 1000.0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("ISR %c: %lu us", b, isrTook);         // how long the ISR took
    lcd.setCursor(0, 1);
    lcd.printf("loop(): %lu ms", stopped / 1000);     // how long loop() was stopped
    now = micros();                     // do not count the time of printing
  }
  last = now;
}
