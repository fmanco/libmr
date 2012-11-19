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
 * Management
 */
void sensors_init     ( void );
void sensors_update   ( void );
void sensors_stop     ( void );


/* ==========================================================================
 * Obstacles detection
 */
int  sensors_obstC     ( void );
int  sensors_obstL     ( void );
int  sensors_obstR     ( void );


/* ==========================================================================
 * Beacon search
 */
bool sensors_beacon    ( void );
bool sensors_beaconDir ( void );


/* ==========================================================================
 * Ground detection
 */
bool sensors_ground    ( void );
bool sensors_groundL   ( void );
bool sensors_groundR   ( void );


/* ==========================================================================
 * Encoders and odometry
 */
void sensors_encoders  ( int* encL, int* encR );
void sensors_odo       ( int* odoL, int* odoR );


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
