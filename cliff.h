#ifndef CLFF_H
#define CLFF_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "uart.h"
#include "movement.h"
#include "driverlib/interrupt.h"

// Global variable declaration
extern bool destination;

// Function Prototypes

/**
 * @brief Moves the robot backward until it is clear of any obstacle.
 *
 * This function checks the signals from the cliff sensors and moves the robot
 * backward until no sensor detects a cliff or a boundary.
 *
 * @param oi A pointer to the open interface structure used to control the robot.
 */
void move_backward_until(oi_t *oi);

/**
 * @brief Moves the robot to a destination marked by the tin foil.
 *
 * This function moves the robot forward while checking all the cliff sensors.
 * Once all sensors detect a foil or surface, it stops and prints a message.
 *
 * @param oi A pointer to the open interface structure used to control the robot.
 */
void move_to_destination(oi_t *oi);

/**
 * @brief Determines the appropriate movement direction based on cliff sensor readings.
 *
 * This function checks the status of each cliff sensor and takes actions
 * (e.g., moving backward, turning left or right) to avoid obstacles or move
 * towards a specific destination.
 *
 * @param oi A pointer to the open interface structure used to control the robot.
 * @param flag A flag indicating whether the robot should avoid a hole (1), a bound (2), or move towards foil (3).
 */
void move_for_flag(oi_t *oi, int flag);

/**
 * @brief Scans the cliff sensors for specific conditions.
 *
 * This function scans the cliff sensors to detect holes, bounds, or foil.
 * It returns a flag indicating which condition the robot has detected.
 *
 * @param oi A pointer to the open interface structure used to control the robot.
 * @return An integer flag: 1 for hole, 2 for bounds, 3 for foil.
 */
int scan_for_cliff(oi_t *oi);

#endif // CLFF_H
