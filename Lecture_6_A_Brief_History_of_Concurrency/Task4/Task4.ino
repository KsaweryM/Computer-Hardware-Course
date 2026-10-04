// Task 4: a race between two tasks.
// 1. Create the tasks incA and incB in setup().
// 2. In loop(), wait until doneA and doneB are both true. Then show on the LCD: "Goal: 2000000" and "Got: " the counter.
// 3. Run it several times. Is the result always the same? Is it ever correct?
// If you finish early: set N = 1000. Is the result correct now? Why?
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int N = 1000000;
volatile int counter = 0;
volatile bool doneA = false;
volatile bool doneB = false;

void incA(void *param) {
  for (int i = 0; i < N; i++)
    counter++;
  doneA = true;
  vTaskDelete(NULL);           // end this task
}

void incB(void *param) {
  for (int i = 0; i < N; i++)
    counter++;
  doneB = true;
  vTaskDelete(NULL);           // end this task
}

void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 1: create the tasks incA and incB.

}

void loop() {
  // TODO 2: when doneA and doneB are both true, show the goal (2 * N) and the counter.

  delay(10);                   // wait without wasting the CPU
}
