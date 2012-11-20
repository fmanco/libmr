/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/robot/actuators.c
 *  \brief Implement actuators interface.
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/actuators.h>
#include <robot/robot.h>


/* ==========================================================================
 * Management
 */

void actuators_init ( void )
{
	robot_setVel2(0, 0);

	robot_setServo(0);

	robot_resetLed(0);
	robot_resetLed(1);
	robot_resetLed(2);
	robot_resetLed(3);
}

void actuators_update ( void )
{

}

void actuators_stop ( void )
{
	robot_setVel2(0, 0);

	robot_setServo(0);

	robot_resetLed(0);
	robot_resetLed(1);
	robot_resetLed(2);
	robot_resetLed(3);
}


/* = EOF ==================================================================== */
