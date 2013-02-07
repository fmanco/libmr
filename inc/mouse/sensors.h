/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/mouse/sensors.h
 *  \brief Read robot sensors' values
 *
 *  The values provided by this library are already filtered and may
 *  even not be based on real sensors but derived from other sensors' values.
 *
 *  \version 0.1.0
 *  \date    Dec 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __MOUSE_SENSORS_H__
#define __MOUSE_SENSORS_H__


#include <base.h>


/* ==========================================================================
 * Configuration values [can be changed]
 */

/**
 *  \brief Thresholds for the binary sensors filtering.
 *
 *  Some binary sensors are filtered using a Schmitt Trigger like algorithm.
 *  Every define of the type <NAME>_ST_THRESHOLD is defining the threshold
 *   for the <NAME> sensor.
 *
 *  For now this MACRO is only used for documentation purposes.
 */
#define ST_THRESHOLD

/**
 *  \brief The #ST_THRESHOLD for the ground detection.
 *
 *  An higher value means that the algorithm will perform slower,
 *   what means, it will take more cycles to accept changes.
 */
#define GROUND_ST_THRESHOLD 5

/**
 *  \brief The #ST_THRESHOLD for the beacon detection.
 *
 *  An higher value means that the algorithm will perform slower,
 *   what means, it will take more cycles to accept changes.
 */
#define BEACON_ST_THRESHOLD 5

/**
 *  \brief The #ST_THRESHOLD for the bump detection.
 *
 *  An higher value means that the algorithm will perform slower,
 *   what means, it will take more cycles to accept changes.
 */
#define BUMP_ST_THRESHOLD   5

/**
 *  \brief Difference (in encoder ticks) between the value applied to the
 *   motors and the value read from the encoders to be considered the
 *   robot is stucked.
 *
 *  This is used when the robot has no bump detection sensor. In this
 *   case the difference between the applied velocity and the read
 *   velocity is used to determine when the robot is stucked.
 */
#define BUMP_THRESHOLD      3


/* ==========================================================================
 * Management
 */

/**
 *  \brief Initalize the sensors module.
 *
 *  This function MUST be called before using this module. It is also
 *   usefull for reseting the module.
 */
void sensors_init     ( void );

/**
 *  \brief Update the sensorial information available.
 *
 *  The necessary sensors reading and calculations are performed when
 *   this function is called. This way the execution of this function
 *   could take some time since reading sensors may be slow.
 */
void sensors_update   ( void );

/**
 *  \brief Stop the sensors module.
 *
 *  This includes disabling sensors to save battery life.
 */
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
int  sensors_beaconDir ( void );


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
#endif /* __MOUSE_SENSORS_H__ */
