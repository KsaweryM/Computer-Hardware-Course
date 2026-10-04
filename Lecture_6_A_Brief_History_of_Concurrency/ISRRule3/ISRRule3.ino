// ISRRule3: an ISR and loop() change one variable. Are presses lost?
// The slides "Rules for an ISR: 3. share data carefully" say: loop() does
//     counted += presses;   // take the new presses
//     presses = 0;          // start again from 0
// If the ISR adds 1 between these two lines, the press is lost, even on one core, even with volatile.
//
// A person cannot press a button exactly between two instructions. So here a TIMER makes the "presses":
// its ISR runs 10 000 times per second, exactly like the ISR of a button.
// A second counter, made, is changed ONLY by the ISR. It says how many presses there really were.
// Every second the sketch compares it with what loop() counted, and shows the difference on the LCD.
// The counters are never reset: made and lost only grow. They are unsigned long (32 bits): after
// 4 294 967 295 they wrap around to 0 by themselves, after about 5 days at 10 000 presses per second.
// made - counted stays correct even then, because unsigned arithmetic wraps around in the same way.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int presses = 0;               // shared: the ISR adds, loop() reads and resets
volatile unsigned long made = 0;        // only the ISR changes it: the true number of presses
hw_timer_t *timer = NULL;

void IRAM_ATTR onPress() {              // the ISR: one "press"
  presses++;
  made++;
}

unsigned long counted = 0;              // all presses that loop() took so far
unsigned long lastReport = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();
  timer = timerBegin(1000000);          // 1 MHz: one step = 1 us
  timerAttachInterrupt(timer, &onPress);
  timerAlarm(timer, 100, true, 0);      // a "press" every 100 us
}

void loop() {
  // the code from the slide
  counted += presses;   // take the new presses
  presses = 0;          // start again from 0

  if (millis() - lastReport >= 1000) {
    timerStop(timer);                   // no more presses for a moment: now the numbers can be compared
    delayMicroseconds(200);             // let an ISR that has already started finish
    counted += presses;                 // the last presses (the ISR cannot run now)
    presses = 0;
    unsigned long lost = made - counted;

    Serial.printf("made: %lu   counted: %lu   lost: %lu\r\n", made, counted, lost);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("made: %lu", made);
    lcd.setCursor(0, 1);
    lcd.printf("lost: %lu", lost);

    lastReport = millis();
    timerStart(timer);
  }
}
