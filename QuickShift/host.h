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
 ** The standard C preprocessor does not prescan arguments which are
 ** stringified, so
 **
 ** @code
 ** #define A B
 ** char const * str = VL_STRINGIFY(A) ;
 ** @endcode
 **
 ** initializes <code>str</code> with a pointer to the string
 ** <code>"A"</code>, which mihgt be unexpected. To fix this issue,
 ** you can use ::VL_XSTRINGIFY.
 **
 ** @sa ::VL_XSTRINGIFY
 **/

#define VL_STRINGIFY(x) # x

/** @brief Expand and then convert the argument to a string
 **
 ** @param x value to be macro-expanded and converted.
 **
 ** This macro macro-expands the argument @a x and stringifies the
 ** result of the expansion. For instance
 **
 ** @code
 ** #define A B
 ** char const * str = VL_STRINGIFY(A) ;
 ** @endcode
 **
 ** initializes <code>str</code> with a pointer to the string
 ** <code>"B"</code>.
 **
 ** @sa ::VL_STRINGIFY
 **/

#define VL_XSTRINGIFY(x) VL_STRINGIFY(x)

/** @brief Concatenate two arguments into a lexical unit
 **
 ** @param x first argument to be concat