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

/* ===================
 * Battery
 */
static int battery = 0;


/* ========================================================================== */

static void handleGroundSensor  ( uint value, int sensNr );
static void updateGroundSensors ( void );
static void updateBattery       ( void );


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

	battery = 0;
}

void sensors_update ( void )
{
	robot_readSensors();
	robot_readEncoders();

	updateGroundSensors();
	updateBattery();
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

/* ===================
 * Battery update
 *  - Read battery voltage (average of the last 32 readings)
 *  - Value is multiplied by 10 (max. value is 101, i.e. 10,1 V)
 */
static void updateBattery ( void )
{
	static int array[32] = {96, 96, 96, 96, 96, 96, 96, 96,
	                        96, 96, 96, 96, 96, 96, 96, 96,
	                        96, 96, 96, 96, 96, 96, 96, 96,
	                        96, 96, 96, 96, 96, 96, 96, 96};
	static int i;
	static int sum = 3072; /* = (96 * 32) */

	uint value;

	value = sensors.battery;

	value = (value * 330 + 511) / 1023;
	value = (value * (3300 + 6800) + 1650) / 33000;

	sum = sum - array[i] + value;
	array[i] = value;
	i = (i + 1) & 0x1F;

	battery = (sum >> 5);
}


/* = EOF ==================================================================== */
