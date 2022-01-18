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
 ** @param x first argument to be concatenated.
 ** @param y second argument to be concatenated.
 **
 ** This macro concatenates its arguments into a single lexical unit
 ** by means of the <code>##</code> preprocessor operator. Notice that
 ** arguments concatenated by <code>##</code> are not pre-expanded by
 ** the C preprocessor. To macro-expand the arguments and then
 ** concatenate them,use ::VL_XCAT.
 **
 ** @see ::VL_XCAT
 **/

#define VL_CAT(x,y) x ## y

/** @brief Expand and then concatenate two arguments into a lexical unit
 **
 ** @param x first argument to be concatenated.
 ** @param y second argument to be concatenated.
 **
 ** This macro is the same as ::VL_CAT, except that the arguments are
 ** macro expanded before being concatenated.
 **
 ** @see ::VL_CAT
 **/

#define VL_XCAT(x,y) VL_CAT(x,y)

/** @brief Expand and then concatenate three arguments into a lexical unit
 **
 ** @param x first argument to be concatenated.
 ** @param y second argument to be concatenated.
 ** @param z third argument to be concatenated.
 **
 ** This macro is the same as ::VL_XCAT, except that it has three arguments.
 **
 ** @see ::VL_XCAT
 **/

#define VL_XCAT3(x,y,z) VL_XCAT(VL_XCAT(x,y),z)

/** @brief Expand and 