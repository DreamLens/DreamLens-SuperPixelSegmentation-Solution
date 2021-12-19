
/** @file    host.c
 ** @author  Andrea Vedaldi
 ** @brief   Host - Definition
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

#include "host.h"
#include "generic.h"
#include <stdio.h>

/**
 @file host.h

 This module provides functionalities to identify the
 host operating system, C compiler,
 and CPU architecture. It also provides a few features
 to abstract from such details.

 - @ref host-os "Host operating system"
 - @ref host-compiler "Host compiler"
   - @ref host-compiler-data-model "Data models"
   - @ref host-compiler-other "Other compiler specific features"
 - @ref host-arch "Host CPU architecture"
   - @ref host-arch-endianness "Endianness"

 @see http://predef.sourceforge.net/index.php

 @section host-os Host operating system

 The module defines a symbol to identify the host operating system:
 ::VL_OS_WIN for Windows, ::VL_OS_LINUX for Linux, ::VL_OS_MACOSX for
 Mac OS X, and so on.

 @section host-compiler Host compiler

 The module defines a symbol to identify the host compiler:
 ::VL_COMPILER_MSC for Microsoft Visual C++, ::VL_COMPILER_GNUC for
 GNU C, and so on. The (integer) value of such symbols corresponds the
 version of the compiler.

 The module defines a symbol to identify the data model of the
 compiler: ::VL_COMPILER_ILP32, ::VL_COMPILER_LP64, or
 ::VL_COMPILER_LLP64 (see Sect. @ref host-compiler-data-model).  For
 convenience, it also defines a number of atomic types of prescribed
 width (::vl_int8, ::vl_int16, ::vl_int32, etc.).

 @remark While some of such functionalities are provided by the
 standard header @c stdint.h, the latter is not supported by all
 platforms.

 @subsection host-compiler-data-model Data models

 The C language defines a number of atomic data types (such as @c
 char, @c short, @c int and so on). The number of bits (width) used to
 represent each data type depends on the compiler data model.  The
 following table summarizes the relevant conventions:

 <table><caption><b>Compiler data models.</b> The table shows
 how many bits are allocated to each atomic data type according to
 each model.</caption>
 <tr style="font-weight:bold;">
 <td>Data model</td>
 <td><code>short</code></td>
 <td><code>int</code></td>
 <td><code>long</code></td>
 <td><code>long long</code></td>
 <td><code>void*</code></td>
 <td>Compiler</td>
 </tr>
 <tr>
 <td>ILP32</td>
 <td style="background-color:#ffa;">16</td>
 <td style="background-color:#afa;">32</td>
 <td style="background-color:#afa;">32</td>
 <td >64</td>
 <td style="background-color:#afa;">32</td>
 <td>common 32 bit architectures</td>
 </tr>
 <tr>
 <td>LP64</td>
 <td style="background-color:#ffa;">16</td>
 <td style="background-color:#afa;">32</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>UNIX-64 (Linux, Mac OS X)</td>
 </tr>
 <tr>
 <td>ILP64</td>
 <td style="background-color:#ffa;">16</td>
 <td>64</td>
 <td>64</td>