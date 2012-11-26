/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/conf.h
 *  \brief This header provides robot dependent configurations.
 *
 *  This header file only provides values that are specific to each physical
 *  robot, and that cannot be assumed to be the same for all robots, or
 *  some constant used by the libraries.
 *
 *  For instance the maximum and minimum values that can be applied on
 *  the servo using the robot library are defined in the robot.h header
 *  file, but the calibration values specific to each servo are defined here.
 *
 *  The values provided in this header file MUST be calibrated for
 *  each robot used. Some utilities are provided for the calibration
 *  of some values.
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_CONF_H__
#define __ROBOT_CONF_H__


#include <base.h>


/* ========================================================================== */

/* ====================
 * Servo calibration values
 */
#define SERVO_WIDTH_MIN  700
#define SERVO_WIDTH_MAX 2200

/* ====================
 * PI Control
 */
#define PI_KP     8
#define PI_KI     3
#define PI_LIMIT 15


/* ========================================================================== */
#endif /* __ROBOT_CONF_H__ */
