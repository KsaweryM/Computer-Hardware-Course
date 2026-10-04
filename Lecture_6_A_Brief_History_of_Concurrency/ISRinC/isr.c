// isr.c: the ISR from the slide "But our ISR is written in C".
// IRAM_ATTR is a macro from the ESP32 libraries (esp_attr.h). Here we define it ourselves,
// so that the file compiles without them.
#define IRAM_ATTR __attribute__((section(".iram1")))

volatile int presses;

void IRAM_ATTR onButtonA() {
  presses++;
}
