/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/robot.h
 *  \brief Implement basic operations on robot (like enabling/disabling sensors)
 *         and robot state database
 *
 *  This functions provide low level actuation on the robot. Besides
 *  robot_init(), that must be called in the beginning of the application,
 *  usually this functions are only necessary for internal library operations.
 *  Use them at your own risk.
 *
 *  Based on mr32 from José Luis Azevedo.
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_ROBOT_H__
#define __ROBOT_ROBOT_H__


#include <base.h>
#include <detpic32.h>


/* ==========================================================================
 * Configuration values [can be changed]
 */

/* ===================
 * Library operation
 * \todo Comment on what this does exactly.
 */
/* #define SOFT_SLOPE */


/* ========================================================================== */

#define SERVO_POS_LEFT  -15
#define SERVO_POS_RIGHT  15

#define M_MAXVEL  100
#define M_MINVEL -100


/* ========================================================================== */

typedef union {
	struct {
		int obst_sens_right;
		int obst_sens_front;
		int obst_sens_left;
		int battery;
		int ground;
		int enc_left;
		int enc_right;
	};

	struct {
		int obst[3];
		int battery;
		int ground;
		int enc[2];
	};

	int array[7];
} mrSens;

typedef struct {
	int vel_right;
	int vel_left;
	int servo_pos;
	int leds;
} mrActs;

typedef union {
	struct {
		uint tick10ms:1;
		uint tick20ms:1;
		uint tick40ms:1;
		uint tick80ms:1;
		uint tick160ms:1;
		uint tick320ms:1;
		uint tick640ms:1;
		uint tick1280ms:1;
	};

	uint ticks;
} mrClock;


/* ========================================================================== */

// \todo Check volatiles
volatile extern mrSens  sensors;
volatile extern mrActs  actuators;
volatile extern mrClock ticker;


/* ==========================================================================
 * Management
 */

/**
 * \brief Initalizes the robot.
 *
 * This function MUST be called before any operation in the robot.
 * Usually this function is called in the beginning of the application.
 */
void robot_init              ( void );

void robot_enableObstSens    ( void );
void robot_disableObstSens   ( void );

void robot_enableGroundSens  ( void );
void robot_disableGroundSens ( void );


/* ==========================================================================
 * Sensors
 */

void robot_readSensors       ( void );
void robot_readEncoders      ( void );
uint robot_readBeaconSens    ( void );

uint robot_startBtn          ( void );
uint robot_stopBtn           ( void );


/* ==========================================================================
 * Actuators
 */

void robot_setVel2           ( int velL, int velR );
void robot_setServo          ( int pos );
void robot_setLed            ( int ledNr );
void robot_resetLed          ( int ledNr );


/* ==========================================================================
 * Utilities
 */

#define waitStep10ms() while(!ticker.tick10ms); ticker.tick10ms = 0
#define waitStep20ms() while(!ticker.tick20ms); ticker.tick20ms = 0
#define waitStep40ms() while(!ticker.tick40ms); ticker.tick40ms = 0
#define waitStep80ms() while(!ticker.tick80ms); ticker.tick80ms = 0


/* ========================================================================== */
#endif /* __ROBOT_ROBOT_H__ */
