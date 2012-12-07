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
#include <robot/state.h>


/* ========================================================================== */

/* ===================
 * Motors
 */
static int spLeft   = 0;
static int spRight  = 0;
static int velLeft  = 0;
static int velRight = 0;

/* ===================
 * Beacon servo
 */
static int servoDegree = 0;


/* ========================================================================== */

#define ENC_DIST_PER_TICK ((WHEEL_CIRC * 1000) / ENC_TPR)  // \todo Check roundings

#define SERVO_DEGREE_RANGE (SERVO_DEGREE_MAX - SERVO_DEGREE_MIN)
#define SERVO_POS_RANGE    (SERVO_POS_RIGHT - SERVO_POS_LEFT)

#define SERVO_DEGREE_TO_POS(degree) \
		(int) ((1.0 * SERVO_POS_RANGE / SERVO_DEGREE_RANGE) * degree)

#define SERVO_POS_TO_DEGREE(pos) \
		(int) (pos / (1.0 * SERVO_POS_RANGE / SERVO_DEGREE_RANGE))


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

	servoDegree = 0;

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

void actuators_setBeaconSens ( int degree )
{
	int pos;
	int effectiveDegree;

	servoDegree = degree;

	pos = SERVO_DEGREE_TO_POS(servoDegree);
	effectiveDegree = SERVO_POS_TO_DEGREE(pos);

	/* \todo Should this be done only on actuators.update?
	 *
	 * If this is to be done here, then we should strictly define
	 *  what is synchronous and what is asynchronous.
	 */
	robot_setServo(pos);
	state_setServoDegree(effectiveDegree);
}

void actuators_rotateBeaconSens ( int degree )
{
	actuators_setBeaconSens(servoDegree + degree);
}

bool actuators_setLed ( uint ledN, bool state )
{
	if (ledN >= N_LEDS)
		return false;

	if (state) {
		robot_setLed(ledN);
	} else {
		robot_resetLed(ledN);
	}

	return true;
}

void actuators_setLeds ( uint bitmap )
{
	uint i;
	uint m;

	for (i = 0, m = 1; i < N_LEDS; i++, m <<= 1) {
		if (bitmap & m) {
			robot_setLed(i);
		} else {
			robot_resetLed(i);
		}
	}
}


/* ========================================================================== */

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
