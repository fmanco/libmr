/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/robot/sensors.c
 *  \brief Implement sensors interface.
 *
 *  \version 0.1.0
 *  \date    Dec 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/robot.h>
#include <robot/sensors.h>
#include <robot/conf.h>
#include <robot/state.h>


/* ========================================================================== */

/* ===================
 * Beacon sensor
 */
static bool beaconOn    = false;
static int  beaconCount = 0;
static int  beaconDir   = 0;

/* ===================
 * Ground sensors
 */
static uint groundCount[5] = {0, 0, 0, 0, 0};
static bool groundOn[5]    = {false, false, false, false, false};

/* ===================
 * Odometry (in millimeters)
 */
static int odoPartLeft  = 0;
static int odoPartRight = 0;
static int odoIntLeft   = 0;
static int odoIntRight  = 0;

/* ===================
 * Battery
 */
static int battery = 0;


/* ========================================================================== */

/*
 * Distance per encoder tick in  micrometers.
 * Micrometers are used because mm would probably lead to truncation.
 */
#define ENC_DIST_PER_TICK ((WHEEL_CIRC * 1000) / ENC_TPR)  // \todo Check roundings


/* ========================================================================== */

static void updateBeacon        ( void );
static void updateGroundSensors ( void );
static void updateBattery       ( void );
static void updateOdometry      ( void );

static inline void stBinSens ( uint value, bool* state, uint* count, uint threshold );


/* ==========================================================================
 * Management
 */

void sensors_init ( void )
{
	int i;

	robot_enableObstSens();
	robot_enableGroundSens();

	beaconOn    = 0;
	beaconCount = 0;
	beaconDir   = 0;

	for (i = 0; i < 5; i++) {
		groundCount[i] = 0;
		groundOn[i] = false;
	}

	odoPartLeft  = 0;
	odoPartRight = 0;
	odoIntLeft   = 0;
	odoIntRight  = 0;

	battery = 0;
}

void sensors_update ( void )
{
	robot_readSensors();
	robot_readEncoders();

	updateBeacon();
	updateGroundSensors();
	updateOdometry();
	updateBattery();
}

void sensors_stop ( void )
{
	robot_disableObstSens();
	robot_disableGroundSens();
}


/* ==========================================================================
 * Obstacles detection
 */

int sensors_obstL ( void )
{
	return sensors.obst_sens_left;
}

int sensors_obstF ( void )
{
	return sensors.obst_sens_front;
}

int sensors_obstR ( void )
{
	return sensors.obst_sens_right;
}


/* ==========================================================================
 * Beacon search
 */

bool sensors_beacon ( void )
{
	return beaconOn;
}

int sensors_beaconDir ( void )
{
	/* Even if the beacon isn't visible
	 * return the last known direction
	 */
	return beaconDir;
}


/* ==========================================================================
 * Target area and line detection (Ground sensors)
 */

bool sensors_groundL ( void )
{
	return groundOn[4];
}

bool sensors_groundCL ( void )
{
	return groundOn[3];
}

bool sensors_groundCF ( void )
{
	return groundOn[2];
}

bool sensors_groundCR ( void )
{
	return groundOn[1];
}

bool sensors_groundR ( void )
{
	return groundOn[0];
}

bool sensors_groundC ( void )
{
	return ((groundOn[1] + groundOn[2] + groundOn[3]) >= 2);
}


/* ==========================================================================
 * Encoders and odometry
 */

void sensors_odoPart ( int* odoL, int* odoR )
{
	if (odoL != NULL) {
		(*odoL) = odoPartLeft / 10000;            // Convert to cm
	}

	if (odoR != NULL) {
		(*odoR) = odoPartRight / 10000;           // Convert to cm
	}
}

void sensors_odoInt ( int* odoL, int* odoR )
{
	if (odoL != NULL) {
		(*odoL) = odoIntLeft / 10000;             // Convert to cm
	}

	if (odoR != NULL) {
		(*odoR) = odoIntRight / 10000;            // Convert to cm
	}
}


/* ==========================================================================
 * Battery level
 */

uint sensors_battery ( void )
{
	return battery;
}


/* ==========================================================================
 * Control buttons
 */

bool sensors_startBtn ( void )
{
	return robot_startBtn();
}

bool sensors_stopBtn ( void )
{
	return robot_stopBtn();
}


/* ========================================================================== */

static void updateBeacon ( void )
{
	stBinSens(robot_readBeaconSens(), &beaconOn, &beaconCount, BEACON_ST_THRESHOLD);

	if (beaconOn)
		beaconDir = state_getServoDegree();
}

static void updateGroundSensors ( void )
{
	int i;
	uint sens = sensors.ground;

	for (i = 0; i < 5; i++) {
		stBinSens((sens & (1 << i)), groundOn + i, groundCount + i, GROUND_ST_THRESHOLD);
	}
}

static void updateOdometry ( void )
{
	odoPartLeft  = ENC_DIST_PER_TICK * (-sensors.enc_left);
	odoPartRight = ENC_DIST_PER_TICK * sensors.enc_right;

	odoIntLeft  += odoPartLeft;
	odoIntRight += odoPartRight;
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

/* ===================
 * Schmitt Trigger like algorithm for handling binary sensors.
 */
static inline void stBinSens ( uint value, bool* state, uint* count, uint threshold )
{
	if (value) {
		if ((*count) < threshold) {
			(*count)++;
		}
	} else {
		if ((*count) > 0) {
			(*count)--;
		}
	}

	if ((*state)) {
		if ((*count) == 0) {
			(*state) = false;
		}
	} else {
		if ((*count) == threshold) {
			(*state) = true;
		}
	}
}


/* = EOF ==================================================================== */
