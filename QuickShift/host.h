/** @file    host.h
 ** @author  Andrea Vedaldi
 ** @brief   Host
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

#ifndef VL_HOST_H
#define VL_HOST_H

/** ------------------------------------------------------------------
 ** @name Configuration options
 ** @{ */

#if defined(__DOXYGEN__)
#define VL_DISABLE_THREADS
#define VL_DISABLE_SSE2
#endif

/** @} */

/** ------------------------------------------------------------------
 ** @name Defining functions
 ** @{ */

#if defined(__DOXYGEN__)
#define VL_EXPORT
#define VL_INLINE
#endif

/** @} */

/** ------------------------------------------------------------------
 ** @name C preprocessor helper macros
 ** @{ */

/** @brief Convert the argument to a string
 **
 ** @param x value to be stringified.
 **
 ** This macro stringifies the argument @a x by means of the
 ** <code>#</code> prerpocessor operator.
 **
 ** The standard C preproce