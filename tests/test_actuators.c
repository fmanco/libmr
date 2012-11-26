/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  tests/test_actuators.c
 *  \brief Tests for actuators module.
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/robot.h>
#include <robot/actuators.h>


/* ========================================================================== */
int main ( void )
{
	printStr("Test Actuators started!");

	robot_init();
	actuators_init();

	while (1) {
		waitStep10ms();

		actuators_update();
	}
}


/* = EOF ==================================================================== */
