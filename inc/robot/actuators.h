/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/actuators.h
 *  \brief Abstraction layer for robot actuation. Allows using of standard
 *         units, like degrees for servo rotation or m/s for wheels speed.
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_ACTUATORS_H__
#define __ROBOT_ACTUATORS_H__


#include <base.h>


/* ==========================================================================
 * Management
 */

void actuators_init    ( void );
void actuators_update  ( void );
void actuators_stop    ( void );


/* ==========================================================================
 * Motors
 */

void actuators_setVel ( int left, int right );
void actuators_getVel ( int* left, int* right );


/* ==========================================================================
 * Beacon sensor's servo
 */

void actuators_setBeaconSens    ( int degree );
void actuators_rotateBeaconSens ( int degree );


/* ==========================================================================
 * Leds
 */

bool actuators_setLed  ( uint ledN, bool state );
void actuators_setLeds ( uint bitmap );


/* ========================================================================== */
#endif /* __ROBOT_ACTUATORS_H__ */
