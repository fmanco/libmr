/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/mouse/mouse.c
 *  \brief Implement mouse interface
 *
 *
 *  \version 0.3.0
 *  \date    Jan 2013
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <mouse/mouse.h>
#include <hal/robot.h>


/* ========================================================================== */

void mouse_init ( void )
{
	robot_init();
}


/* ==========================================================================
 * Timer
 */

inline void waitStep10ms ( void )
{
	while(!ticker.tick10ms);
	ticker.tick10ms = 0;
}

inline void waitStep20ms ( void )
{
	while(!ticker.tick10ms);
	ticker.tick10ms = 0;
}

inline void waitStep40ms ( void )
{
	while(!ticker.tick10ms);
	ticker.tick10ms = 0;
}

inline void waitStep80ms ( void )
{
	while(!ticker.tick10ms);
	ticker.tick10ms = 0;
}


/* = EOF ==================================================================== */
