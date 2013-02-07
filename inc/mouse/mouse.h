/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  mouse.h
 *  \brief Provide generic low level functions.
 *
 *  This module provides low level functions like robot initialization
 *   or a timer.
 *
 *  \version 0.3.0
 *  \date    Jan 2013
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __MOUSE_MOUSE_H__
#define __MOUSE_MOUSE_H__


#include <base.h>


/* ========================================================================== */

/**
 *  \brief Initialize all necessary systems to use the robot.
 *
 *  This function must be called before any robot operation, i.e., before
 *   almost any other function from mrlib library.
 */
void mouse_init ( void );


/* ==========================================================================
 * Timer
 */

/**
 *  \brief Wait for the next 10ms tick
 *
 *  The wait is done be pooling. After the waiting
 *   the correspondent timer flag is cleared.
 */
inline void waitStep10ms ( void );

/**
 *  \brief Wait for the next 20ms tick
 *
 *  The wait is done be pooling. After the waiting
 *   the correspondent timer flag is cleared.
 */
inline void waitStep20ms ( void );

/**
 *  \brief Wait for the next 40ms tick
 *
 *  The wait is done be pooling. After the waiting
 *   the correspondent timer flag is cleared.
 */
inline void waitStep40ms ( void );

/**
 *  \brief Wait for the next 80ms tick
 *
 *  The wait is done be pooling. After the waiting
 *   the correspondent timer flag is cleared.
 */
inline void waitStep80ms ( void );


/* ========================================================================== */
#endif /* __MOUSE_MOUSE_H__ */
