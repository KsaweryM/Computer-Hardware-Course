// Task 5: a race between two tasks.
// 1. Start two incTask tasks with the same priority, with &doneA and &doneB as parameters.
// 2. In loop(), wait until both are done. Then show on the LCD: "Goal: 2000000" and "Got: N".
// 3. Run it several times. Is N always the same? Is it ever correct?
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int N = 1000000;
volatile int counter = 0;
volatile bool doneA = false, doneB = false;

void incTask(void *param) {
  for (int i = 0; i < N; i++) {
    counter++;
  }
  *(volatile bool *)param = true;   // done
  vTaskDelete(NULL);                // end this task
}

void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 1: create the two tasks.

}

void loop() {
  // TODO 2: when doneA and doneB are both true, show the goal (2 * N) and the counter.

  delay(10);                        // wait without wasting the CPU
}
