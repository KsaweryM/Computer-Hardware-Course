// Mini-project 3: back to the ESP32. A producer and a consumer on the microcontroller.
// The ISR of button A is the producer: it puts each press into a FreeRTOS queue.
// A task is the consumer: it takes the presses out of the queue and shows the count on the LCD.
// The circuit: button A on GPIO 5, the LCD on I2C (SDA = GPIO 8, SCL = GPIO 9).
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_A = 5;
QueueHandle_t presses;          // the queue: a ready bounded buffer

void IRAM_ATTR onButtonA() {    // the ISR: the producer
  static uint32_t n = 0;
  n++;                          // the number of this press
  // TODO 2: put n into the queue with xQueueSendFromISR(presses, &n, NULL).
  //         An ISR must never wait: if the queue is full, the press is lost.
}

void lcdTask(void *param) {     // the task: the consumer
  for (;;) {
    uint32_t n;
    // TODO 3: take the next press out of the queue with xQueueReceive(presses, &n, portMAX_DELAY).
    //         While the queue is empty, the task is Blocked.

    // TODO 4: show "Presses: n" on the LCD.
  }
}

void setup() {
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();

  // TODO 1: create the queue with 10 places for uint32_t: xQueueCreate(10, sizeof(uint32_t)).

  xTaskCreate(lcdTask, "lcd", 4096, NULL, 1, NULL);
  pinMode(BUTTON_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonA, FALLING);
}

void loop() {
  delay(1000);                  // nothing to do here: the ISR and the task do the work
}
