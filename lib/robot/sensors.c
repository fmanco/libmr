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


/* ========================================================================== */

/* ===================
 * Ground sensors
 */
static uint groundCount[5] = {0, 0, 0, 0, 0};
static bool groundOn[5]    = {false, false, false, false, false};


/* ========================================================================== */

static void handleGroundSensor  ( uint value, int sensNr );
static void updateGroundSensors ( void );


/* ==========================================================================
 * Management
 */

void sensors_init ( void )
{
	int i;

	robot_enableObstSens();
	robot_enableGroundSens();

	for (i = 0; i < 5; i++) {
		groundCount[i] = 0;
		groundOn[i] = false;
	}
}

void sensors_update ( void )
{
	robot_readSensors();
	robot_readEncoders();

	updateGroundSensors();
}

void sensors_stop ( void )
{
	robot_disableObstSens();
	robot_disableGroundSens();
}


/* ========================================================================== */

static inline void handleGroundSensor ( uint value, int sensNr )
{
	if (value) {
		if (groundCount[sensNr] < GROUND_ST_THRESHOLD)
			groundCount[sensNr]++;
	} else {
		if (groundCount[sensNr] > 0)
			groundCount[sensNr]--;
	}

	if (groundOn[sensNr]) {
		if (groundCount[sensNr] == 0)
			groundOn[sensNr] = false;
	} else {
		if (groundCount[sensNr] == GROUND_ST_THRESHOLD)
			groundOn[sensNr] = true;
	}
}

static void updateGroundSensors ( void )
{
	int i;
	uint sens = sensors.ground;

	for (i = 0; i < 5; i++) {
		handleGroundSensor((sens & (1 << i)), i);
	}
}


/* = EOF ==================================================================== */
