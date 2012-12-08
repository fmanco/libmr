/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/state.h
 *  \brief This module allows for information exchange between
 *         the middleware, usually, between sensors and actuators modules.
 *
 *
 *  \version 0.1.0
 *  \date    Dec 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_STATE_H__
#define __ROBOT_STATE_H__


#include <base.h>


/* ========================================================================== */

/**
 * \brief Define the last effective servo degree.
 *
 * This is not the raw degree applied by the user but the degree
 *  with the necessary roundings.
 *
 * \param degree The efective servo degree.
 */
inline void state_setServoDegree ( int degree );

/**
 * \brief Get the last announced servo degree.
 *
 * \returns The servo degreee.
 */
inline int  state_getServoDegree ( void );

/**
 * \brief Define the last setpoints applied to the motors.
 *
 * \param left  The SP applied to the left motor.
 * \param right The SP applied to the right motor.
 */
inline void state_setSP ( int left, int right );

/**
 * \brief Get the last setpoints applied to the motors.
 *
 * The arguments can be NULL, in wich case the value is not returned.
 * This is usefull for retrieving only one of the values.
 *
 * \param left Pointer to the location
 *         where the left SP is to be stored, or NULL.
 * \param right Pointer to the location
 *         where the left SP is to be stored, or NULL.
 */
inline void state_getSP ( int* left, int* right );


/* ========================================================================== */
#endif /* __ROBOT_STATE_H__ */
