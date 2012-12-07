/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/robot/state.c
 *  \brief Implement the state exchange area.
 *
 *  This module is basically a set of shared
 *   variables with setters and getters.
 *
 *
 *  \version 0.1.0
 *  \date    Dec 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/state.h>


/* ========================================================================== */

static int servoDegree = 0;


/* ========================================================================== */

inline void state_setServoDegree ( int degree )
{
	servoDegree = degree;
}

inline int state_getServoDegree ( void )
{
	return servoDegree;
}


/* = EOF ==================================================================== */
