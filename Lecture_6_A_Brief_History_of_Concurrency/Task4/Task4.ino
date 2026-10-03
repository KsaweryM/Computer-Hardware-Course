// Task 4: three LEDs as three tasks.
// 1. Create three tasks with xTaskCreate: LED 1 changes every 300 ms, LED 2 every 500 ms, LED 3 every 700 ms.
// 2. loop() still shows "Loop: N". Do the LEDs keep their rhythm?
// 3. In the task of LED 3, replace vTaskDelay with a busy wait:
//      unsigned long t = millis();
//      while (millis() - t < 700) { }
//    Do the other LEDs still blink? Then create this task with priority 2. What happens?
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED1 = 4, LED2 = 7, LED3 = 3;
long loops = 0;

// Hint: one function can serve all three tasks. Pass the pin and the period through param:
struct Blink { int pin; int ms; };
Blink b1 = {LED1, 300}, b2 = {LED2, 500}, b3 = {LED3, 700};

// TODO 1: the task function blinkTask(void *param): an endless loop that toggles
//         its LED and waits with vTaskDelay(pdMS_TO_TICKS(...)).


void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 2: create three tasks with xTaskCreate, one for each Blink.

}

void loop() {
  loops++;
  lcd.setCursor(0, 1);
  lcd.print("Loop: ");
  lcd.print(loops);
}
