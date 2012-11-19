/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/robot/sensors.c
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/robot.h>
#include <robot/sensors.h>


/* ==========================================================================
 * Management
 */

void sensors_init ( void )
{
	robot_enableObstSens();
	robot_enableGroundSens();
}

void sensors_update ( void )
{
	robot_readSensors();
	robot_readEncoders();
}

void sensors_stop ( void )
{
	robot_disableObstSens();
	robot_disableGroundSens();
}


/* = EOF ==================================================================== */
