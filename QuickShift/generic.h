
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
 ** ::VL_TYPE_UINT8, ::VL_TYPE_UINT16, ::VL_TYPE_UINT32, ::VL_TYPE_UINT64.
 **/

VL_INLINE char const *
vl_get_type_name (vl_type type)
{
  switch (type) {
    case VL_TYPE_FLOAT   : return "float"  ;
    case VL_TYPE_DOUBLE  : return "double" ;
    case VL_TYPE_INT8    : return "int8"   ;
    case VL_TYPE_INT16   : return "int16"  ;
    case VL_TYPE_INT32   : return "int32"  ;
    case VL_TYPE_INT64   : return "int64"  ;
    case VL_TYPE_UINT8   : return "int8"   ;
    case VL_TYPE_UINT16  : return "int16"  ;
    case VL_TYPE_UINT32  : return "int32"  ;
    case VL_TYPE_UINT64  : return "int64"  ;
    default: return NULL ;
  }
}

/** @brief Get data type size.
 ** @param type data type.
 ** @return size (in byte)
 **
 ** @c type is one of ::VL_TYPE_FLOAT, ::VL_TYPE_DOUBLE,
 ** ::VL_TYPE_INT8, ::VL_TYPE_INT16, ::VL_TYPE_INT32, ::VL_TYPE_INT64,
 ** ::VL_TYPE_UINT8, ::VL_TYPE_UINT16, ::VL_TYPE_UINT32, ::VL_TYPE_UINT64.
 **/

VL_INLINE vl_size
vl_get_type_size (vl_type type)
{
  vl_size dataSize = 0 ;
  switch (type) {
    case VL_TYPE_DOUBLE : dataSize = sizeof(double) ; break ;
    case VL_TYPE_FLOAT  : dataSize = sizeof(float) ; break ;
    case VL_TYPE_INT64  : case VL_TYPE_UINT64 : dataSize = sizeof(vl_int64) ; break ;
    case VL_TYPE_INT32  : case VL_TYPE_UINT32 : dataSize = sizeof(vl_int32) ; break ;
    case VL_TYPE_INT16  : case VL_TYPE_UINT16 : dataSize = sizeof(vl_int16) ; break ;
    case VL_TYPE_INT8   : case VL_TYPE_UINT8  : dataSize = sizeof(vl_int8)  ; break ;
    default:
      abort() ;
  }
  return dataSize ;
}

/** @} */

/** ------------------------------------------------------------------
 ** @name Library state and configuration
 ** @{ */

/** @internal @brief VLFeat thread state */
typedef struct _VlThreadSpecificState
{
  /* errors */
  int lastError ;
  char lastErrorMessage [VL_ERR_MSG_LEN] ;

  /* random number generator */
  VlRand rand ;

  /* time */
#if defined(VL_OS_WIN)
  LARGE_INTEGER ticFreq ;
  LARGE_INTEGER ticMark ;
#else
  clock_t ticMark ;
#endif
} VlThreadSpecificState ;

/** @internal @brief VLFeat global state */
typedef struct _VlState
{

#if ! defined(VL_DISABLE_THREADS)
#if   defined(VL_THREADS_POSIX)
  pthread_key_t threadKey ;
  pthread_mutex_t mutex ;
  pthread_t mutexOwner ;
  pthread_cond_t mutexCondition ;
  size_t mutexCount ;
#elif defined(VL_THREADS_WIN)
  DWORD tlsIndex ;
  CRITICAL_SECTION mutex ;
#endif
#else
  VlThreadSpecificState * threadState ;
#endif

  int   (*printf_func)  (char const * format, ...) ;
  void *(*malloc_func)  (size_t) ;
  void *(*realloc_func) (void*,size_t) ;
  void *(*calloc_func)  (size_t, size_t) ;
  void  (*free_func)    (void*) ;

#if defined(VL_ARCH_IX86) || defined(VL_ARCH_X64) || defined(VL_ARCH_IA64)
  VlX86CpuInfo cpuInfo ;
#endif
  int numCPUs ;

  vl_bool simdEnabled ;
  int maxNumThreads ;

} VlState ;

/** @internal @brief VLFeat global state */
VL_EXPORT VlState _vl_state ;

VL_INLINE VlState * vl_get_state () ;
VL_INLINE VlThreadSpecificState * vl_get_thread_specific_state () ;
VL_EXPORT void vl_lock_state () ;
VL_EXPORT void vl_unlock_state () ;
VL_EXPORT VlThreadSpecificState * vl_thread_specific_state_new () ;