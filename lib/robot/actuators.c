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
#include <robot/conf.h>


/* ========================================================================== */

/* ===================
 * Motors
 */
static int spLeft   = 0;
static int spRight  = 0;
static int velLeft  = 0;
static int velRight = 0;


/* ========================================================================== */

#define ENC_DIST_PER_TICK ((WHEEL_CIRC * 1000) / ENC_TPR)  // \todo Check roundings


/* ========================================================================== */

static void motorsPI ( void );


/* ==========================================================================
 * Management
 */

void actuators_init ( void )
{
	spLeft   = 0;
	spRight  = 0;
	velLeft  = 0;
	velRight = 0;

	robot_setVel2(0, 0);

	robot_setServo(0);

	robot_resetLed(0);
	robot_resetLed(1);
	robot_resetLed(2);
	robot_resetLed(3);
}

void actuators_update ( void )
{
	motorsPI();
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


/* ==========================================================================
 * Motors
 */

void actuators_setVel ( int left, int right )
{
	/* See! You don't even have to think:
	 *
	 * vel (cm / s), DPT (um), T (ms)
	 *
	 * vel  cm ----- 1 s
	 * dist mm ----- T ms
	 *
	 * dist = ((T x (vel x 10)) / 1000) mm
	 *
	 *
	 * DPT  um ----- 1  tick
	 * dist mm ----- sp ticks
	 *
	 * sp = ((T x vel x 10) / DPT)
	 *
	 */

	velLeft  = left;
	velRight = right;

	spLeft   = (CICLE_T * left  * 10) / ENC_DIST_PER_TICK;
	spRight  = (CICLE_T * right * 10) / ENC_DIST_PER_TICK;
}

void actuators_getVel ( int* left, int* right )
{
	if (left != NULL) {
		(*left) = velLeft;
	}

	if (right != NULL) {
		(*right) = velRight;
	}
}



static void motorsPI ( void )
{
	static int intL = 0;
	static int intR = 0;

	int encL, encR;
	int errL, errR;

	encL = sensors.enc_left;
	encR = sensors.enc_right;

	errL = spLeft  - encL;
	errR = spRight - encR;

	intL += errL;
	intR += errR;

	intL = (intL > PI_LIMIT ? PI_LIMIT : (intL < -PI_LIMIT ? -PI_LIMIT : intL));
	intR = (intR > PI_LIMIT ? PI_LIMIT : (intR < -PI_LIMIT ? -PI_LIMIT : intR));

	robot_setVel2((PI_KP * errL) + (PI_KI * intL), (PI_KP * errR) + (PI_KP * intR));
}

/* = EOF ==================================================================== */
