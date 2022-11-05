
/** @file    mathop.h
 ** @brief   Math operations
 ** @author  Andrea Vedaldi
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

#ifndef VL_MATHOP_H
#define VL_MATHOP_H

#include "generic.h"
#include <math.h>

/** @brief Logarithm of 2 (math constant)*/
#define VL_LOG_OF_2 0.693147180559945

/** @brief Pi (math constant) */
#define VL_PI 3.141592653589793

/** @brief IEEE single precision epsilon (math constant)
 **
 ** <code>1.0F + VL_EPSILON_F</code> is the smallest representable
 ** single precision number greater than @c 1.0F. Numerically,
 ** ::VL_EPSILON_F is equal to @f$ 2^{-23} @f$.
 **
 **/
#define VL_EPSILON_F 1.19209290E-07F

/** @brief IEEE double precision epsilon (math constant)
 **
 ** <code>1.0 + VL_EPSILON_D</code> is the smallest representable
 ** double precision number greater than @c 1.0. Numerically,
 ** ::VL_EPSILON_D is equal to @f$ 2^{-52} @f$.
 **/
#define VL_EPSILON_D 2.220446049250313e-16

/*
   For the code below: An ANSI C compiler takes the two expressions,
   LONG_VAR and CHAR_VAR, and implicitly casts them to the type of the
   first member of the union. Refer to K&R Second Edition Page 148,
   last paragraph.
*/

/** @internal @brief IEEE single precision quiet NaN constant */
static union { vl_uint32 raw ; float value ; }
  const vl_nan_f =
    { 0x7FC00000UL } ;

/** @internal @brief IEEE single precision infinity constant */
static union { vl_uint32 raw ; float value ; }
  const vl_infinity_f =
    { 0x7F800000UL } ;

/** @internal @brief IEEE double precision quiet NaN constant */
static union { vl_uint64 raw ; double value ; }
  const vl_nan_d =
#ifdef VL_COMPILER_MSC
    { 0x7FF8000000000000ui64 } ;
#else
    { 0x7FF8000000000000ULL } ;
#endif

/** @internal @brief IEEE double precision infinity constant */
static union { vl_uint64 raw ; double value ; }
  const vl_infinity_d =
#ifdef VL_COMPILER_MSC
    { 0x7FF0000000000000ui64 } ;
#else
    { 0x7FF0000000000000ULL } ;
#endif

/** @brief IEEE single precision NaN (not signaling) */
#define VL_NAN_F (vl_nan_f.value)

/** @brief IEEE single precision positive infinity (not signaling) */
#define VL_INFINITY_F (vl_infinity_f.value)

/** @brief IEEE double precision NaN (not signaling) */
#define VL_NAN_D (vl_nan_d.value)

/** @brief IEEE double precision positive infinity (not signaling) */
#define VL_INFINITY_D (vl_infinity_d.value)

/* ---------------------------------------------------------------- */

/** @brief Fast <code>mod(x, 2 * VL_PI)</code>
 **
 ** @param x input value.
 ** @return <code>mod(x, 2 * VL_PI)</code>
 **
 ** The function is optimized for small absolute values of @a x.
 **
 ** The result is guaranteed to be not smaller than 0. However, due to
 ** finite numerical precision and rounding errors, the result can be
 ** equal to 2 * VL_PI (for instance, if @c x is a very small negative
 ** number).
 **/

VL_INLINE float
vl_mod_2pi_f (float x)
{
  while (x > (float)(2 * VL_PI)) x -= (float) (2 * VL_PI) ;
  while (x < 0.0F) x += (float) (2 * VL_PI);
  return x ;
}

/** @brief Fast <code>mod(x, 2 * VL_PI)</code>
 ** @see vl_mod_2pi_f
 **/

VL_INLINE double
vl_mod_2pi_d (double x)
{
  while (x > 2.0 * VL_PI) x -= 2 * VL_PI ;
  while (x < 0.0) x += 2 * VL_PI ;
  return x ;
}

/** @brief Fast <code>(int) floor(x)</code>
 ** @param x argument.
 ** @return @c (int) floor(x)
 **/

VL_INLINE int
vl_floor_f (float x)
{
  int xi = (int) x ;
  if (x >= 0 || (float) xi == x) return xi ;
  else return xi - 1 ;
}

/** @brief Fast <code>(int) floor(x)</code>
 ** @see vl_floor_f
 **/

VL_INLINE int
vl_floor_d (double x)
{
  int xi = (int) x ;
  if (x >= 0 || (double) xi == x) return xi ;
  else return xi - 1 ;
}

/** @brief Fast @c abs(x)
 ** @param x argument.
 ** @return @c abs(x)
 **/

VL_INLINE float
vl_abs_f (float x)
{
#ifdef VL_COMPILER_GNU
  return __builtin_fabsf (x) ;
#else
  return fabsf(x) ;
#endif
}

/** @brief Fast @c abs(x)
 ** @sa vl_abs_f
 **/

VL_INLINE double
vl_abs_d (double x)
{
#ifdef VL_COMPILER_GNU
  return __builtin_fabs (x) ;
#else
  return fabs(x) ;
#endif
}

VL_INLINE double
vl_log2_d (double x)
{
#ifdef VL_COMPILER_GNU
  return __builtin_log2(x) ;