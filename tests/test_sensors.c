/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  tests/test_sensors.c
 *  \brief Tests for sensors module.
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/robot.h>
#include <robot/sensors.h>


/* ========================================================================== */

int main ( void )
{
	printStr("Test Sensors started!");

	robot_init();
	sensors_init();

	while (1) {
		waitStep10ms();

		sensors_update();

		int odoPL = 0, odoPR = 0;
		int odoIL = 0, odoIR = 0;

		sensors_odoPart (&odoPL, &odoPR);
		sensors_odoInt  (&odoIL, &odoIR);

		printf("%3d %3d %3d | %d | %d%d%d%d%d | %3d %3d %5d %5d | %3d | %d%d\n",
			sensors_obstL(), sensors_obstF(), sensors_obstR(),
			sensors_beacon(),
			sensors_groundL(), sensors_groundCL(), sensors_groundCF(), sensors_groundCR(), sensors_groundR(),
			odoPL, odoPR, odoIL, odoIR,
			sensors_battery(),
			sensors_startBtn(), sensors_stopBtn());
	}
}


/* = EOF ==================================================================== */
