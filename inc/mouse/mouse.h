/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/mouse/mouse.h
 *  \brief Provide generic low level functions.
 *
 *  This module provides low level functions like robot initialization,
 *   robot reset and timers.
 *
 *  \version 0.4.0
 *  \date    Feb 2013
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
 *  This function *must be called* before any robot operation, i.e., before
 *   almost any other function from libmr library.
 */
void mouse_init ( void );


/* ==========================================================================
 * Timer
 */

/**
 *  \brief Wait for the next 10ms tick
 *
 *  The wait is done by pooling.
 */
inline void mouse_waitStep10ms ( void );

/**
 *  \brief Wait for the next 20ms tick
 *
 *  The wait is done by pooling.
 */
inline void mouse_waitStep20ms ( void );

/**
 *  \brief Wait for the next 40ms tick
 *
 *  The wait is done by pooling.
 */
inline void mouse_waitStep40ms ( void );

/**
 *  \brief Wait for the next 80ms tick
 *
 *  The wait is done by pooling.
 */
inline void mouse_waitStep80ms ( void );


/* ========================================================================== */
#endif /* __MOUSE_MOUSE_H__ */
