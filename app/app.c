/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  app/app.c
 *  \brief An example application for libmr
 *
 *  This can be used as a base template for a libmr based application.
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>


/* ========================================================================== */

int main ( void )
{
	// mlogInfo(&log, "Jerry is born!");

	/* ======================================================================
	 * Setup
	 */
	// mlogInfo(&log, "Initializing machinery ...");

	/// \todo Initialization code goes here

	// mlogInfo(&log, "Every systems up!");


	/* ======================================================================
	 * Main loop
	 */
	// mlogInfo(&log, "Press start to begin the search!");

	// util_waitStart();

	// mlogInfo(&log, "Let the search begin!");

	// while (!state_isFinished()) {
		// util_waitStep10ms();       // Cycle time is 10ms

		// sensors_update();          // Read sensors to get the results from
		                           //  the last cycle actuation


		/// \todo Application code goes here


		// lowlevel_implement();      // Implement low level behaviours

		// actuators_update();        // Apply changes to actuators
	// }

	// mlogInfo(&log, "I got the there!");

	// mlogInfo(&log, "Shuting down systems...");

	/// \todo Stop code goes here

	// mlogInfo(&log, "Jerry is terminated!");

	return 0;
}


/* = EOF ==================================================================== */
