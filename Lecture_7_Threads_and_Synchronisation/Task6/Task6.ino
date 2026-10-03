// Task 6: fix Monday's Task 5 with a FreeRTOS mutex.
// 1. Create the mutex in setup(), and lock and unlock it around counter++.
// 2. Run it several times. What does the LCD show now?
// 3. Is it faster or slower than on Monday? Why?
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int N = 1000000;
volatile int counter = 0;
volatile bool doneA = false, doneB = false;
SemaphoreHandle_t m;                // the mutex

void incTask(void *param) {
  for (int i = 0; i < N; i++) {
    // TODO 2: lock the mutex: xSemaphoreTake(m, portMAX_DELAY);
    counter++;
    // TODO 3: unlock the mutex: xSemaphoreGive(m);
  }
  *(volatile bool *)param = true;   // done
  vTaskDelete(NULL);                // end this task
}

void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 1: create the mutex with xSemaphoreCreateMutex(), before the tasks.

  xTaskCreate(incTask, "incA", 2048, (void *)&doneA, 1, NULL);
  xTaskCreate(incTask, "incB", 2048, (void *)&doneB, 1, NULL);
}

void loop() {
  if (doneA && doneB) {
    lcd.setCursor(0, 0);
    lcd.print("Goal: ");
    lcd.print(2 * N);
    lcd.setCursor(0, 1);
    lcd.print("Got:  ");
    lcd.print(counter);
    while (true) delay(1000);
  }
  delay(10);                        // wait without wasting the CPU
}
