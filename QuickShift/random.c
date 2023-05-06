
/** @file    random.c
 ** @brief   Random number generator - Definition
 ** @author  Andrea Vedaldi
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

/** @file random.h

 This module implements the popular Mersenne Twister algorithm (MATLAB
 random generator from version 7.4).

 @section random-overview Overview

 A random number generator can be initalized by

 @code
 VlRand rand ;
 vl_rand_init (&rand) ;
 @endcode

 ::VlRand is a simple structure holding the state of the
 random number generator. The generator can be seeded by
 ::vl_rand_seed and ::vl_rand_seed_by_array. For intsance:

 @code
 vl_rand_seed (&rand, clock()) ;
 @endcode

 The generator can be used to obtain random quantities of
 various types:

 - ::vl_rand_int31, ::vl_rand_uint32 for 32-bit random integers;
 - ::vl_rand_real1 for a double in [0,1];
 - ::vl_rand_real2 for a double in [0,1);
 - ::vl_rand_real3 for a double in (0,1);
 - ::vl_rand_res53 for a double in [0,1) with high resolution.

 There is no need to explicitly destroy a ::VlRand instance.

 [1] http://en.wikipedia.org/wiki/Mersenne_twister

**/

#include "random.h"

/*
A C-program for MT19937, with initialization improved 2002/1/26.
Coded by Takuji Nishimura and Makoto Matsumoto.

Before using, initialize the state by using init_genrand(seed)
or init_by_array(init_key, keySize).

Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The names of its contributors may not be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

