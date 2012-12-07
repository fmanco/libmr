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


/* ========================================================================== */
#endif /* __ROBOT_STATE_H__ */
