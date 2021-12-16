
/** @file    generic.h
 ** @author  Andrea Vedaldi
 ** @brief   Generic
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

#ifndef VL_GENERIC_H
#define VL_GENERIC_H

#include "host.h"
#include "random.h"

#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>

#if defined(VL_OS_WIN)
#include <Windows.h>
#endif

#if ! defined(VL_DISABLE_THREADS) && defined(VL_THREADS_POSIX)
#include <pthread.h>
#endif

/** @brief Library version string */
#define VL_VERSION_STRING "0.9.13"

/** @brief Maximum length (in characters) of an error message */
#define VL_ERR_MSG_LEN 1024

/** @name Type identidifers for atomic data types
 ** @{ */

#define VL_TYPE_FLOAT   1     /**< @c float type */
#define VL_TYPE_DOUBLE  2     /**< @c double type */
#define VL_TYPE_INT8    3     /**< @c ::vl_int8 type */
#define VL_TYPE_UINT8   4     /**< @c ::vl_uint8 type */
#define VL_TYPE_INT16   5     /**< @c ::vl_int16 type */
#define VL_TYPE_UINT16  6     /**< @c ::vl_uint16 type */
#define VL_TYPE_INT32   7     /**< @c ::vl_int32 type */
#define VL_TYPE_UINT32  8     /**< @c ::vl_uint32 type */
#define VL_TYPE_INT64   9     /**< @c ::vl_int64 type */
#define VL_TYPE_UINT64  10    /**< @c ::vl_uint64 type */

typedef vl_uint32 vl_type ;

/** @brief Get the name of a data type.
 ** @param type data type.
 ** @return data name of the data type.
 **
 ** @c type is one of ::VL_TYPE_FLOAT, ::VL_TYPE_DOUBLE,
 ** ::VL_TYPE_INT8, ::VL_TYPE_INT16, ::VL_TYPE_INT32, ::VL_TYPE_INT64,