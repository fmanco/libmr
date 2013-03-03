/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/mouse/actuators.h
 *  \brief Robot actuation module.
 *
 *  The actuators module is the module responsible to provide an abstraction
 *   to the robot actuators.
 *
 *  This module assumes a robot with the following characteristics:
 *   - Differential steering (two similar, parallel and independent wheels);
 *   - A beacon sensor hooked up to a rotary platform;
 *   - A set of LEDs available for the user.
 *
 *  With the provided functions you can specify low level actuation
 *   using standard units such as cm/s or degrees.
 *
 *  The changes are only applied when actuators_update() is called, and not
 *   immediately after the call to the function. The changes actually applied
 *   to the robot are the last ones requested by a call to the correspondent
 *   function of the module.
 *
 *  \version 0.4.0
 *  \date    Feb 2013
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __MOUSE_ACTUATORS_H__
#define __MOUSE_ACTUATORS_H__


#include <base.h>


/* ==========================================================================
 * Management
 */

/**
 *  \brief Initialize actuators module.
 *
 *  This function resets the actuators module in order it can be used, and
 *   enable it. This function should be called before start using the module
 *   or whenever you want to reset it.
 *
 *  *The changes are applied immediately*, without calling actuators_update().
 */
void actuators_init    ( void );

/**
 *  \brief Apply the requested changes to the actuators.
 *
 *  The changes actually applied to the robot are the last ones
 *   requested by a call to a function.
 */
void actuators_update  ( void );

/**
 *  \brief Perform the necessary changes in order to stop the robot.
 *
 *  This method put all actuators in the default state, and disable the
 *   usage of this module.
 *
 *  The default state is:
 *   - Both motors stoped;
 *   - Beacon sensor in the center position;
 *   - All LEDs turned off.
 *
 *  *The changes are applied immediately*, without calling actuators_update().
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
 *  \brief Get the velocity values that will be applied next.
 *
 *  This function doesn't return the current motors velocities. It does
 *   return the values that will be applied to the robot if actuators_update()
 *   was called at this moment.
 *
 *  Notice the values returned value can be different from the ones provided
 *   with the actuators_setVel() function, because of constraints of the robot
 *   (maximum velocity) or rounding of the values.
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
 *  The maximum and minimun position depends upont the servo used. The values
 *   will be clipped to the limits when necessary.
 *
 *  The sensor is considered to be in the position 0 degres when it
 *   is pointing forward. The position increase clockwise, what means that
 *   to rotate the servo clockwise a positive value should be provided
 *   and to rotate it anticlockwise a negative value should be provided.
 *
 *  \param degree The next position to apply to the beacon sensor.
 */
void actuators_setBSensPos ( int degree );

/**
 *  \brief Rotate the beacon sensor relatively to the current position.
 *
 *  The value should be provided in the degrees, and indicates how much
 *   the sensor should be rotated from it's current position. The changes
 *   are only applied in the next call to actuators_update().
 *
 *  Check actuators_setBSensPos() for more details.
 *
 *  \param degree The value in degrees the sensor should
 *                be rotated from it's current position.
 */
void actuators_rotateBSens ( int degree );

/**
 *  \brief Get the beacon sensor position that will be applied next.
 *
 *  This function doesn't return the current position. It does
 *   return the values that will be applied to the robot if actuators_update()
 *   was called at this moment.
 *
 *  Notice the values returned value can be different from the ones provided
 *   with the actuators_setBSensPos() or actuators_rotateBSens()
 *   functions, because of constraints of the robot (position limits) or rounding
 *   of the values.
 *
 *  \param degree Location where the value of the position should be stored.
 */
void actuators_getBSensPos ( int* degree );


/* ==========================================================================
 * Leds
 */

/**
 *  \brief Set the state of a led.
 *
 *  A true value will turn on the led, and a false value will turn it off.
 *
 *  If you try to set a led that doesn't exist then nothing happens and
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
#endif /* __MOUSE_ACTUATORS_H__ */
