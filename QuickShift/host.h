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

/** @brief Expand and then concatenate four arguments into a lexical unit
 **
 ** @param x first argument to be concatenated.
 ** @param y second argument to be concatenated.
 ** @param z third argument to be concatenated.
 ** @param u fourth argument to be concatenated.
 **
 ** This macro is the same as ::VL_XCAT, except that it has four arguments.
 **
 ** @see ::VL_XCAT
 **/

#define VL_XCAT4(x,y,z,u) VL_XCAT(VL_XCAT3(x,y,z),u)

/** @brief Expand and then concatenate five arguments into a lexical unit
 **
 ** @param x first argument to be concatenated.
 ** @param y second argument to be concatenated.
 ** @param z third argument to be concatenated.
 ** @param u fourth argument to be concatenated.
 ** @param v fifth argument to be concatenated.
 **
 ** This macro is the same as ::VL_XCAT, except that it has five arguments.
 **
 ** @see ::VL_XCAT
 **/

#define VL_XCAT5(x,y,z,u,v) VL_XCAT(VL_XCAT4(x,y,z,u),v)

/** @} */

/** @brief Convert a boolean to "yes" or "no" strings
 ** @param x boolean to convert.
 ** A pointer to either the string "yes" (if @a x is true)
 ** or the string "no".
 ** @par Example
 ** @code
 ** VL_PRINTF("Is x true? %s.", VL_YESNO(x))
 ** @endcode
 **/

#define VL_YESNO(x) ((x)?"yes":"no")

/*
 The following macros identify the host OS, architecture and compiler.
 They are derived from http://predef.sourceforge.net/
 */

/** @name Identifying the host operating system
 ** @{ */
#if defined(linux)     || \
    defined(__linux)   || \
    defined(__linux__) || \
    defined(__DOXYGEN__)
#define VL_OS_LINUX 1
#define VL_THREADS_POSIX 1
#endif

#if (defined(__APPLE__) & defined(__MACH__)) || \
     defined(__DOXYGEN__)
#define VL_OS_MACOSX 1
#define VL_THREADS_POSIX 1
#endif

#if defined(__WIN32__) || \
    defined(_WIN32)    || \
    defined(__DOXYGEN__)
#define VL_OS_WIN 1
#define VL_THREADS_WIN 1
#endif

#if defined(_WIN64) || \
    defined(__DOXYGEN__)
#define VL_OS_WIN64 1
#define VL_THREADS_WIN 1
#endif
/** @} */

/** @name Identifying the host compiler
 ** @{ */
#if defined(__GNUC__) || defined(__DOXYGEN__)
# if defined(__GNUC_PATCHLEVEL__)
#  define VL_COMPILER_GNUC (__GNUC__ * 10000 \
+ __GNUC_MINOR__ * 100 \
+ __GNUC_PATCHLEVEL__)
# else
#  define VL_COMPILER_GNUC (__GNUC__ * 10000 \
+ __GNUC_MINOR__ * 100)
# endif
#endif

#if defined(_MSC_VER) || defined(__DOXYGEN__)
#define VL_COMPILER_MSC _MSC_VER
#endif

#if defined(__LCC__) || defined(__DOXYGEN__)
#warning "LCC support is experimental!"
#define VL_COMPILER_LCC 1
#endif
