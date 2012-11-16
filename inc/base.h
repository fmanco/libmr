/* ==========================================================================
 * mrlib - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  inc/base.h
 *  \brief Basic definitions and utilities for mrlib
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#ifndef __BASE_H__
#define __BASE_H__


#include <stddef.h>
#include <stdbool.h>


/* ==========================================================================
 * Standard typedefs
 */
typedef unsigned char  uchar
typedef unsigned short ushort
typedef unsigned int   uint
typedef unsigned long  ulong


/* ==========================================================================
 * Util Macros
 */
#define abs(val) (val > 0 ? val : -val)


/* ========================================================================== */
#endif /* __BASE_H__ */
