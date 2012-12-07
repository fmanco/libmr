/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/robot/sensors.h
 *  \brief Read robot sensors' values
 *
 *  The values provided by this library are already filtered and may
 *  even not be based on real sensors but derived from other sensors' values.
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __ROBOT_SENSORS_H__
#define __ROBOT_SENSORS_H__


#include <base.h>


/* ==========================================================================
 * Configuration values [can be changed]
 */

#define GROUND_ST_THRESHOLD 5
#define BEACON_ST_THRESHOLD 5


/* ==========================================================================
 * Management
 */

void sensors_init     ( void );
void sensors_update   ( void );
void sensors_stop     ( void );


/* ==========================================================================
 * Obstacles detection
 */

int  sensors_obstL     ( void );
int  sensors_obstF     ( void );
int  sensors_obstR     ( void );


/* ==========================================================================
 * Beacon search
 */

bool sensors_beacon    ( void );
bool sensors_beaconDir ( void );


/* ==========================================================================
 * Target area and line detection (Ground sensors)
 */

/**
 * \brief Get the *left most* ground sensor state.
 *
 * The value provided was properly filtered.
 *
 * \return true if the sensor is on and false otherwise
 */
bool sensors_groundL   ( void );

/**
 * \brief Get the *center left* ground sensor state.
 *
 * The value provided was properly filtered.
 *
 * \return true if the sensor is on and false otherwise
 */
bool sensors_groundCL  ( void );

/**
 * \brief Get the *center front* ground sensor state.
 *
 * The value provided was properly filtered.
 *
 * \return true if the sensor is on and false otherwise
 */
bool sensors_groundCF  ( void );

/**
 * \brief Get the *center right* ground sensor state.
 *
 * The value provided was properly filtered.
 *
 * \return true if the sensor is on and false otherwise
 */
bool sensors_groundCR  ( void );

/**
 * \brief Get the *right most* ground sensor state.
 *
 * The value provided was properly filtered.
 *
 * \return true if the sensor is on and false otherwise
 */
bool sensors_groundR   ( void );

/**
 * \brief Get the state of the center ground sesnsor using
 *        a combination of the three center sensors.
 *
 * The values used by this function are properly filtered.
 *
 * \return true if at least two of the three center sensors
 *         are on and false otherwise
 */
bool sensors_groundC   ( void );


/* ==========================================================================
 * Encoders and odometry
 */

void sensors_odoPart   ( int* odoL, int* odoR );
void sensors_odoInt    ( int* odoL, int* odoR );


/* ==========================================================================
 * Compass (simulated)
 */

int  sensors_compass   ( void );


/* ==========================================================================
 * Battery level
 */

uint sensors_battery   ( void );


/* ==========================================================================
 * Bump detection
 */

bool sensors_bump      ( void );


/* ==========================================================================
 * Control buttons
 */

bool sensors_startBtn ( void );
bool sensors_stopBtn  ( void );


/* ========================================================================== */
#endif /* __ROBOT_SENSORS_H__ */
