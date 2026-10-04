// The parts of the robot: ready, you do not need to change them.
#pragma once

/**
 * @brief Sets up all the parts of the robot. Call it first in setup().
 */
void setupRobot();

/**
 * @brief Measures the distance to the obstacle. It takes 40 ms.
 * @return the distance in cm (400 when nothing is in front)
 */
int measureCm();

/**
 * @brief Shows a distance on the LCD.
 * @param cm the distance in cm
 */
void showDistance(int cm);

/**
 * @brief One short beep (100 ms).
 */
void beep();

/**
 * @brief The wheels turn forward, until stop() is called.
 */
void forward();

/**
 * @brief The wheels turn backward, until stop() is called.
 */
void backward();

/**
 * @brief The wheels stop.
 */
void stop();
