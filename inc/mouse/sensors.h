/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/mouse/sensors.h
 *  \brief Provide sensory information from the robot sensors.
 *
 *  The sensors module is the responsible for providing you with the sensory
 *   information from your robot.
 *
 *  This module assumes a robot with the following sensors:
 *   - A beacon sensor on top of the robot: this is a sensor that
 *     indicates if the beacon is visible or not, and also the angular
 *     position of the beacon, relatively to the robot;
 *   - Three obstacle sensors positioned in the front of the robot: this
 *     sensors provide the distance to the closest obstacle in range. The
 *     orientation of the sensors may differ depending on the device, but
 *     usually there will be one pointing forward and two pointing left and
 *     right at a determined angle;
 *   - A ground sensor array: this array is composed by five sensors, usually
 *     positioned in the front of the robot, that indicate wether the ground
 *     bellow them is dark or not;
 *   - An odometry module;
 *   - A compass;
 *   - A bump detection sensor that indicates if the robot is stuck;
 *   - A battery sensor that provides information about the battery level.
 *   - Two buttons, one called start button and other called stop button;
 *
 *  The real robot may not have all of this sensors. In that case, one of
 *   two things may happen:
 *   - The sensor readings are returned by the functions don't represent
 *     anything (probably will allway be zero);
 *   - The sensor information is derived from other sensors.
 *
 *  The robot can have more sensors than the ones presented above. That sensors
 *   may be used to provide the information provided by this module, but are
 *   not directly accessible through it.
 *
 *  To check wether a sensor really exists or not check the device
 *   specific implementation.
 *
 *  The information provided by this module is properly processed, in order to:
 *   - Filter the low level data removing noise;
 *   - Convert units (to ones usable by humans);
 *   - Create virtual sensors.
 *
 *  Finally, the reading of the sensors is performed only when the
 *   sensors_update() function is called.
 *
 *  \version 0.4.0
 *  \date    Feb 2013
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __MOUSE_SENSORS_H__
#define __MOUSE_SENSORS_H__


#include <base.h>


/* ==========================================================================
 * Constants
 */

/**
 *  \brief Infinite value for obstacle sensors.
 *
 *  \todo [LOW] Probably 1000 is not the best value.
 *
 *  The obstacle sensors have a limited range. When nothing is visible
 *   (within the range of the sensors) this value is returned by the
 *   functions meaning that nothing is visible and so it is impossible
 *   to know where the closest obstacle is.
 */
#define OBST_SENS_INFINITE 1000


/* ==========================================================================
 * Management
 */

/**
 *  \brief Initalize the sensors module.
 *
 *  This function *MUST* be called before using this module. It is also
 *   usefull for reseting the module in case you want to restart the robot.
 */
void sensors_init   ( void );

/**
 *  \brief Update the sensory information.
 *
 *  This function updates the internal module sensory information by
 *   by performing readings of the real sensors and the necessary
 *   calculations.
 *
 *  It is the information collected (and calculated) by a call to
 *   this function that is provided when you call a reading function
 *   of this module.
 *
 *  Warning: A call to this function will trigger sensors readings
 *   what will probably take some time. Also, a call to this function is
 *   blocking, meaning only when all the information is collected (sensors
 *   are read) and calculations made this function returns.
 */
void sensors_update ( void );

/**
 *  \brief Stop the sensors module.
 *
 *  This includes disabling sensors to save battery life.
 */
void sensors_stop   ( void );


/* ==========================================================================
 * Obstacles detection
 */

/**
 *  \brief Provide the distance to the closest obstacle to the *left* sensor.
 *
 *  The distance is provided in cm.
 *
 *  If there are no objects within the range of the sensor the speciall
 *   value #OBST_SENS_INFINITE is returned.
 *
 *  The information provided by this function is the one updated by the
 *   last call to sensors_update(), what means that consecutive calls
 *   to this function without calling sensors_update() will allways
 *   return the same value.
 *
 *  \returns The distance to the closest obstacle to the left sensor in cm,
 *            or #OBST_SENS_INFINITE.
 */
int  sensors_obstL ( void );

/**
 *  \brief Provide the distance to the closest obstacle to the *front* sensor.
 *
 *  The distance is provided in cm.
 *
 *  If there are no objects within the range of the sensor the speciall
 *   value #OBST_SENS_INFINITE is returned.
 *
 *  The information provided by this function is the one updated by the
 *   last call to sensors_update(), what means that consecutive calls
 *   to this function without calling sensors_update() will allways
 *   return the same value.
 *
 *  \returns The distance to the closest obstacle to the front sensor in cm,
 *            or #OBST_SENS_INFINITE.
 */
int  sensors_obstF ( void );

/**
 *  \brief Provide the distance to the closest obstacle to the *right* sensor.
 *
 *  The distance is provided in cm.
 *
 *  If there are no objects within the range of the sensor the speciall
 *   value #OBST_SENS_INFINITE is returned.
 *
 *  The information provided by this function is the one updated by the
 *   last call to sensors_update(), what means that consecutive calls
 *   to this function without calling sensors_update() will allways
 *   return the same value.
 *
 *  \returns The distance to the closest obstacle to the right sensor in cm,
 *            or #OBST_SENS_INFINITE.
 */
int  sensors_obstR ( void );


/* ==========================================================================
 * Beacon search
 */

/**
 *  \brief Indicate wether the beacon is visible or not.
 *
 *  The information provided by this function is the one updated by the
 *   last call to sensors_update(), what means that consecutive calls
 *   to this function without calling sensors_update() will allways
 *   return the same value.
 *
 *  \returns true if the beacon is visible and false otherwise.
 */
bool sensors_beacon    ( void );

/**
 *  \brief Provide the beacon direction.
 *
 *  The direction is given in degrees using the robot as the referencial.
 *
 *  \returns The beacon direction.
 */
int  sensors_beaconDir ( void );


/* ==========================================================================
 * Ground detection
 */

/**
 *  \brief Provide the *left most* ground sensor state.
 *
 *  The value provided is properly filtered. The parameters used are:
 *   - # GROUND_ST_THRESHOLD.
 *
 *  \returns true if the sensor is on and false otherwise.
 */
bool sensors_groundL  ( void );

/**
 *  \brief Provide the *center left* ground sensor state.
 *
 *  The value provided is properly filtered. The parameters used are:
 *   - # GROUND_ST_THRESHOLD.
 *
 *  \returns true if the sensor is on and false otherwise.
 */
bool sensors_groundCL ( void );

/**
 *  \brief Provide the *center front* ground sensor state.
 *
 *  The value provided is properly filtered. The parameters used are:
 *   - # GROUND_ST_THRESHOLD.
 *
 *  \return true if the sensor is on and false otherwise.
 */
bool sensors_groundCF ( void );

/**
 *  \brief Provide the *center right* ground sensor state.
 *
 *  The value provided is properly filtered. The parameters used are:
 *   - # GROUND_ST_THRESHOLD.
 *
 *  \returns true if the sensor is on and false otherwise.
 */
bool sensors_groundCR ( void );

/**
 *  \brief Provide the *right most* ground sensor state.
 *
 *  The value provided is properly filtered. The parameters used are:
 *   - # GROUND_ST_THRESHOLD.
 *
 *  \returns true if the sensor is on and false otherwise.
 */
bool sensors_groundR  ( void );

/**
 *  \brief Get the state of the center ground sesnsor.
 *
 *  This information is provided using a combination of the three
 *   center sensors. It considers the three sensors as one and indicates
 *   the state of the majority of the sensors.
 *
 *  The values used by this function are properly filtered. The parameters are:
 *   - # GROUND_ST_THRESHOLD
 *
 *  \returns true if the sensor is on and false otherwise. This basically
 *           indicates the state of the majority of the three sensors.
 */
bool sensors_groundC  ( void );


/* ==========================================================================
 * Robot position and direction
 */

/**
 *  \brief Provides the position of the robot relative to the start position.
 *
 *  The X axis is the one with direction of 0 degrees, and the Y axis the one
 *   with the direction of 90 degress.
 *
 *  The position can be determined in a lot of different ways, dependent on
 *   the sensors available on the specific robot. The position can (and
 *   probably is) an estimations so it can have a lot of error.
 *
 *  \returns The robot position relative to the start position.
 */
void sensors_position ( int* posX, int* posY );

/**
 *  \brief Provides the position of the robot relative to last reading.
 *
 *  This function differs from sensors_position() because it measures the
 *   position relatively to the place the robot was the last time this function
 *   was called.
 *
 *  The X axis is the one with direction of 0 degrees, and the Y axis the one
 *   with the direction of 90 degress.
 *
 *  The position can be determined in a lot of different ways, dependent on
 *   the sensors available on the specific robot. The position can (and
 *   probably is) an estimations so it can have a lot of error.
 *
 *  \returns The robot position relative to the last reading.
 */
void sensors_movement ( int* posX, int* posY );

/**
 *  \brief Provides the direction of the robot.
 *
 *  The reference depends upon the robot. It is usually North but can also
 *   be the robot start orientation or any other.
 *
 *  \returns The direction of the robot in degrees.
 */
int  sensors_compass  ( void );


/* ==========================================================================
 * Battery state
 */

/**
 *  \brief Provides the battery level.
 *
 *  The value is given in percentage.
 *
 *  \returns The level of the battery in percentage.
 */
uint sensors_battery ( void );


/* ==========================================================================
 * Bump detection
 */

/**
 *  \briefs Indicates whether the robot hit something.
 *
 *  This function returns true during all the time the robot is hitting
 *   something. Is usefull to know if the robot is stuck.
 *
 *  \returns True if the robot is hitting something and false otherwise.
 */
bool sensors_bump ( void );


/* ==========================================================================
 * Control buttons
 */

/**
 *  \brief Provides the state of the start button.
 *
 *  Start is only the name of the button. It's real function is undefined
 *   and depends on how you use it.
 *
 *  \returns True if the button is pressed, and false otherwise.
 */
bool sensors_startBtn ( void );

/**
 *  \brief Provides the state of the stop button.
 *
 *  Stop is only the name of the button. It's real function is undefined
 *   and depends on how you use it.
 *
 *  \returns True if the button is pressed, and false otherwise.
 */
bool sensors_stopBtn  ( void );


/* ========================================================================== */
#endif /* __MOUSE_SENSORS_H__ */
