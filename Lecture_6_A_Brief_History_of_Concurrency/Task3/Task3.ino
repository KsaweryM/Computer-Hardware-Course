#include "robot.h"
// Task 3: program the robot.

/***************************************************************************************************
 * THE ROBOT MANUAL                                                                                *
 *                                                                                                 *
 *                                     distance sensor                                             *
 *                                   .-----------------.                                           *
 *                                   |  (O)       (O)  |                                           *
 *                                   '-----------------'                                           *
 *            left wheel                     ||                     right wheel                    *
 *            .-------.                      ||                      .-------.                     *
 *            |    /  |   .-------.     .-----------.   .-------.    |    /  |                     *
 *            |   o   |===| A4988 |=====|  ESP32-C3 |===| A4988 |====|   o   |                     *
 *            |       |   '-------'     |           |   '-------'    |       |                     *
 *            '-------'     driver      '-----------'     driver     '-------'                     *
 *                                           ||                                                    *
 *                                           ||====(( o ))  buzzer                                 *
 *                                           ||                                                    *
 *                                   .-----------------.                                           *
 *                                   | distance: 25 cm |  LCD                                      *
 *                                   '-----------------'                                           *
 *                                                                                                 *
 * The robot has two wheels, a distance sensor, a buzzer and the LCD.                              *
 * Make it drive forward while the obstacle is at least 20 cm away.                                *
 * When the obstacle is closer than 20 cm, the robot stops and beeps until the way is free again.  *
 * All the time, the LCD shows the distance.                                                       *
 **************************************************************************************************/

/**
 * void setupRobot()
 * @brief Sets up all the parts of the robot. Call it first in setup().
 */

/**
 * int measureCm()
 * @brief Measures the distance to the obstacle. It takes 40 ms.
 * @return the distance in cm (400 when nothing is in front)
 */

/**
 * void showDistance(int cm)
 * @brief Shows a distance on the LCD.
 * @param cm the distance in cm
 */

/**
 * void beep()
 * @brief One short beep (100 ms).
 */

/**
 * void forward()
 * @brief The wheels turn forward, until stop() is called.
 */

/**
 * void backward()
 * @brief The wheels turn backward, until stop() is called.
 */

/**
 * void stop()
 * @brief The wheels stop.
 */

/**
 * @brief The distance to the obstacle in cm.
 * The task watch writes it, the other tasks only read it.
 */
volatile int distance = 400;

/**
 * @brief The task watch (ready): every 100 ms it measures the distance and prints it in the Serial Monitor.
 * Run it and move the slider of the sensor (click the sensor in Wokwi).
 * Write the other tasks in the same way.
 * @param param not used
 */
void watch(void *param) {
  for (;;) {
    distance = measureCm();
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print(" cm\r\n");
    delay(100);
  }
}

/**
 * @brief The task show: every 200 ms it shows the distance on the LCD.
 * @param param not used
 */
void show(void *param) {
  for (;;) {
    /** @todo call showDistance(distance), then wait 200 ms */
  }
}

/**
 * @brief The task drive: every 50 ms it checks the distance.
 * At least 20 cm: the wheels turn forward. Less: the wheels stop.
 * @param param not used
 */
void drive(void *param) {
  for (;;) {
    /** @todo forward() when distance >= 20, else stop(), then wait 50 ms */
  }
}

/**
 * @brief The task warn: every 500 ms it beeps, when the distance is less than 20 cm.
 * @param param not used
 */
void warn(void *param) {
  for (;;) {
    /** @todo beep() when distance < 20, then wait 500 ms */
  }
}

/**
 * @brief Sets up the robot and creates the tasks.
 */
void setup() {
  setupRobot();
  /** tasks that print need a bigger stack than 2048 bytes */
  xTaskCreate(watch, "watch", 4096, NULL, 1, NULL);

  /** @todo create the task show */

  /** @todo create the task drive */

  /** @todo create the task warn */
}

/**
 * @brief We do not need loop(): the tasks do all the work.
 */
void loop() {
  vTaskDelete(NULL);           // end the task that runs loop()
}

/***************************************************************************************************
 * FINISHED EARLY? EXTEND THE ROBOT WITH SOME OF THESE:                                            *
 *                                                                                                 *
 * 1. A parking sensor: the robot beeps also while it drives.                                      *
 *    The closer the obstacle, the faster it beeps: after each beep, wait distance * 10 ms.        *
 *                                                                                                 *
 * 2. A countdown: when the robot was stopped and the way becomes free, it does not start at once. *
 *    First it beeps for 3 s, once per second, and only then it drives.                            *
 *                                                                                                 *
 * 3. Backing up: when the robot stands for more than 2 s, it drives backward for 1 s, then stops. *
 *    Use backward().                                                                              *
 **************************************************************************************************/