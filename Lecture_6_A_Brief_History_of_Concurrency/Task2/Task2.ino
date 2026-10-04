// Task 2: three LEDs, one timer.
// Make LED 1, 2 and 3 change every 300, 500 and 700 ms with ONE timer:
// a tick every 100 ms, as on the slide "The tick in the code".
// Run it: do the LEDs blink as in Simulator 2?
const int LED1 = 4, LED2 = 7, LED3 = 3;

hw_timer_t *timer = nullptr;
volatile unsigned long ticks = 0;
volatile bool led1, led2, led3;   // global variables: false at the start

// TODO 1: the timer ISR onTick(). Count the ticks, and toggle each LED on its own tick
//         (LED 1 every 3 ticks, LED 2 every 5, LED 3 every 7).


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // TODO 2: start the timer with a tick every 100 ms: timerBegin, timerAttachInterrupt, timerAlarm.

}

void loop() {
  // nothing here: the timer does the work
}
