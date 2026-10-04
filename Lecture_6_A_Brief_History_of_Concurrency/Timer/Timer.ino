// Timer: a timer interrupt blinks the LED (the code from the slides "A timer in the code").
// The circuit: the LED on GPIO 4, as in the project Circuit.
// 1. Does the LED change every 500 ms?
// 2. Change 500000 to 100000. What happens?
// 3. loop() is empty. Who switches the LED?

const int LED = 4;
hw_timer_t *timer = nullptr;
volatile bool ledOn = false;

void IRAM_ATTR onTimer() {        // the ISR
  ledOn = !ledOn;
  digitalWrite(LED, ledOn);
}

void setup() {
  pinMode(LED, OUTPUT);
  timer = timerBegin(1000000);              // 1 MHz: the counter grows by 1 every 1 us
  timerAttachInterrupt(timer, &onTimer);    // which ISR runs
  timerAlarm(timer, 500000, true, 0);       // ring after 500 000 us = 500 ms, start again, forever
}

void loop() {
  // nothing here: the timer calls onTimer
}
