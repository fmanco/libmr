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

static int spLeft      = 0;
static int spRight     = 0;


/* ========================================================================== */

inline void state_setServoDegree ( int degree )
{
	servoDegree = degree;
}

inline int state_getServoDegree ( void )
{
	return servoDegree;
}

inline void state_setSP ( int left, int right )
{
	spLeft  = left;
	spRight = right;
}

inline void state_getSP ( int* left, int* right )
{
	if (left != NULL) {
		(*left) = spLeft;
	}

	if (right != NULL) {
		(*right) = spRight;
	}
}


/* = EOF ==================================================================== */
