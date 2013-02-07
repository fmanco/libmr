/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
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
#include <mouse/mouse.h>
#include <mouse/actuators.h>
#include <detpic32.h>


/* ========================================================================== */

int main ( void )
{
	printStr("Test Actuators started!");

	mouse_init();
	actuators_init();

	while (1) {
		waitStep10ms();

		actuators_update();
	}
}


/* = EOF ==================================================================== */
