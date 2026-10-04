// The parts of the robot: ready, you do not need to change them.
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "robot.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static const int TRIG = 0, ECHO = 1;  // the distance sensor (HC-SR04)
static const int STEP = 4, DIR = 5;   // the wheels (two stepper motors with A4988 drivers)
static const int BUZZER = 10;

static volatile unsigned long echoStart, echoUs;

static void IRAM_ATTR onEcho() {      // the ISR of ECHO: notes when the echo pulse starts and ends
  if (digitalRead(ECHO) == HIGH) echoStart = micros();
  else echoUs = micros() - echoStart;
}

void setupRobot() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  attachInterrupt(ECHO, onEcho, CHANGE);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, HIGH);            // forward
  ledcAttach(STEP, 500, 8);           // a pulse on STEP 500 times per second, when forward() is on
}

int measureCm() {
  echoUs = 0;
  digitalWrite(TRIG, HIGH);           // a 10 us pulse: the sensor sends a short sound
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delay(40);                          // the echo comes back within 40 ms
  if (echoUs == 0) return 400;        // no echo: nothing in front
  return echoUs / 58;                 // there and back: 58 us = 1 cm
}

void showDistance(int cm) {
  lcd.setCursor(0, 0);
  lcd.print("distance:       ");      // 16 characters: clears the old number
  lcd.setCursor(10, 0);
  lcd.print(cm);
  lcd.print(" cm");
}

void beep() {
  tone(BUZZER, 1000, 100);            // 1000 Hz for 100 ms
}

void forward() {
  digitalWrite(DIR, HIGH);            // forward
  ledcWrite(STEP, 128);               // the hardware makes the pulses: 500 steps per second
}

void backward() {
  digitalWrite(DIR, LOW);             // backward
  ledcWrite(STEP, 128);
}

void stop() {
  ledcWrite(STEP, 0);
}
