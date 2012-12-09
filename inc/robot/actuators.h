/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/actuators.h
 *  \brief Abstraction layer for robot actuation. Allows using of standard
 *         units, like degrees for servo rotation or m/s for wheels speed.
 *
 *
 *  \version 0.2.0
 *  \date    Dec 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_ACTUATORS_H__
#define __ROBOT_ACTUATORS_H__


#include <base.h>


/* ==========================================================================
 * Management
 */

/**
 *  \brief Initialize actuators module.
 *
 *  This function resets the actuators module in order it can be used.
 *   It should be called before start using the module
 *   or if you want to reset it.
 *
 *  The changes performed to the state of the robot are immediately
 *   applied, without calling actuators_update().
 */
void actuators_init    ( void );

/**
 *  \brief Apply the requested changes to the actuators.
 *
 *  The changes actually applied to the robot are the last ones requested.
 *  This is, if actuators_setVel() is called twice only the last call will take effect.
 */
void actuators_update  ( void );

/**
 *  \brief Perform the necessary changes in order to stop the robot.
 *
 *  This method put all actuators in the default state. The changes
 *   are applied immediately.
 */
void actuators_stop    ( void );


/* ==========================================================================
 * Motors
 */

/**
 *  \brief Set the motors velocity.
 *
 *  Velocities should be provided for both motors, in cm/s. A negative
 *   velocity indicates the robot should move backwards. The maximum
 *   velocity depends upon the robot used.
 *
 *  The changes are only applied when actuators_update() is called.
 *
 *  \param left Velocity to apply to the left motor.
 *  \param right Velocity to apply to the right motor.
 */
void actuators_setVel ( int left, int right );

/**
 *  \brief Get the last velocitie values requested by calling actuators_setVel().
 *
 *  This function doesn't return the actual motors velocities. It does
 *   return the last values passed to actuators_setVel() as arguments.
 *
 *  If you are only interested in one of the values, simple give `NULL` to the
 *   other argument. Obviously both arguments can be `NULL` but I
 *   don't see the point.
 *
 *  \param left Location where the value for the left motor should be stored
 *              or `NULL` if you're not interested in this value.
 *
 *  \param right Location where the value for the right motor should be stored
 *               or `NULL` if you're not interested in this value.
 */
void actuators_getVel ( int* left, int* right );


/* ==========================================================================
 * Beacon sensor's servo
 */

/**
 *  \brief Set the beacon sensor degree to a determined position.
 *
 *  The value should be provided in the degrees. The change are only
 *   applied in the next call to actuators_update().
 *
 *  The maximum and minimun position depends upont the servo used. If the
 *   values provided exceeds the maximum position, the servo is set to the
 *   maximum.
 *
 *  The sensor is considered to be in the position 0 degres when it
 *   is pointing forward. The position increase clockwise, what means
 *   to rotate the servo clockwise a positive value should be provided
 *   and to rotate it anticlockwise a negative value should be provided.
 *
 *  To define the maximum degree the sensor could reach set the values in
 *   the configuration module (inc/robot/conf.h).
 *
 *  \param degree The next position to apply to the beacon sensor.
 */
void actuators_setBeaconSens    ( int degree );

/**
 *  \brief Rotate the beacon sensor relatively to the current position.
 *
 *  The value should be provided in the degrees, and indicates how much
 *   the sensor should be rotated. The changes are only applied in the
 *   next call to actuators_update().
 *
 *  Check actuators_setBeaconSens() for more details.
 *
 *  \param degree The value in degrees the sensor should
 *                be rotated from it's current position.
 */
void actuators_rotateBeaconSens ( int degree );


/* ==========================================================================
 * Leds
 */

/**
 *  \brief Set the state of a led.
 *
 *  A true value will turn on the led, and a false value will turn it off.
 *
 *  If you try to set a led that doesn't exist then nothing happens, but
 *   false is returned.
 *
 *  \param ledN The led number to actuate on.
 *  \param state The state to be applied to the led. True will turn the led
 *               on and false will turn it off.
 *
 *  \returns True if the led exists and false otherwise.
 */
bool actuators_setLed  ( uint ledN, bool state );

/**
 *  \brief Set the state of all the leds at once.
 *
 *  Each bit of the bitmap is interpreted as the state of the led
 *   correspondent to the bit position. Bit zero applies to
 *   led zero, an so on.
 *
 *  Check actuators_setLed() for more details.
 *
 *  \param bitmap The state to be set on the leds.
 */
void actuators_setLeds ( uint bitmap );


/* ========================================================================== */
#endif /* __ROBOT_ACTUATORS_H__ */
