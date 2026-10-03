// Task 2: three LEDs, one timer.
// 1. Make LED 1 blink every 500 ms with a timer interrupt.
// 2. Then: one tick every 100 ms, and LED 1, 2, 3 change every 300, 500 and 700 ms.
// 3. loop() counts as fast as it can and shows "Loop: N". Do the LEDs keep their rhythm?
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_A = 5;
const int LED1 = 4, LED2 = 7, LED3 = 3;

volatile int presses = 0;      // from Task 1
long loops = 0;

void IRAM_ATTR onButtonA() {   // from Task 1
  presses++;
}

hw_timer_t *timer = nullptr;

// TODO 1: the timer ISR, for example onTick().
//         Question 1: toggle LED 1.
//         Question 2: count the ticks, and toggle each LED on its own tick
//         (LED 1 every 3 ticks, LED 2 every 5, LED 3 every 7).


void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();
  pinMode(BUTTON_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonA, FALLING);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // TODO 2: start the timer: timerBegin, timerAttachInterrupt, timerAlarm.

}

void loop() {
  loops++;
  lcd.setCursor(0, 0);
  lcd.print("Presses: ");
  lcd.print(presses);
  lcd.setCursor(0, 1);
  lcd.print("Loop: ");
  lcd.print(loops);
}
