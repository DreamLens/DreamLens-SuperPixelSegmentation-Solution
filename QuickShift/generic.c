
/** @file    generic.c
 ** @author  Andrea Vedaldi
 ** @brief   Generic - Definition
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

/**
 @mainpage VLFeat -- Vision Lab Features Library

 @version __VLFEAT_VERSION__
 @author Andrea Vedaldi  (vedaldi@cs.ucla.edu)
 @author Brian Fulkerson (bfulkers@cs.ucla.edu)

 @par Copyright &copy; 2007-11 Andrea Vedaldi and Brian Fulkerson

 <em>VLFeat C library contains implementations of common computer
 vision algorithms, with a special focus on visual features for
 matching image regions. Applications include structure from motion
 and object and category detection and recognition.

 We strive to make the library free of clutter, portable (VLFeat is
 largely C-89 compatible), and self- documented. Different parts of
 the library are weakly interdependent, simplifying understanding and
 extraction of code.</em>

 @section main-contents Contents

 - Algorithms
   - @ref sift.h     "Scale Invariant Feature Transform (SIFT)"
   - @ref dsift.h    "Dense SIFT (DSIFT)"
   - @ref mser.h     "Maximally Stable Extremal Regions (MSER)"
   - @ref kmeans.h   "K-means"
   - @ref ikmeans.h  "Integer K-means (IKM)"
   - @ref hikmeans.h "Hierarchical Integer K-means (HIKM)"
   - @ref aib.h      "Agglomerative Information Bottleneck (AIB)"
   - @ref quickshift.h "Quick shift image segmentation"
   - @ref kdtree.h   "KDTree (fast and approximate nearest neighbors)"
   - @ref homkermap.h "Homogeneous kernel map"
   - @ref pegasos.h  "PEGASOS SVM solver"
 - Support functionalities
   - @ref host.h      "Platform abstraction"
   - @ref generic.h   "Errors, memory, logging, and others"
   - @ref random.h    "Random number generator"
   - @ref mathop.h    "Math operations"
   - @ref heap-def.h  "Generic heap object (priority queue)"
   - @ref stringop.h  "String operations"
   - @ref imopv.h     "Image operations"
   - @ref pgm.h       "PGM reading and writing"
   - @ref rodrigues.h "Rodrigues formula"
   - @ref mexutils.h  "MATLAB MEX helper functions"
   - @ref getopt_long.h "Drop-in @c getopt_long replacement"
 - @ref design          "Design Concepts"
   - @ref design-objects     "Objects"
   - @ref design-resources   "Memory and resource management"
   - @ref design-threads     "Multi-threading"
   - @ref design-portability "Portability"
 - @ref main-glossary "Glossary"

 @section design VLFeat design concepts

 VLFeat is designed to be portable and simple to integrate with high
 level languages such as MATLAB. This section illustrates and
 motivates the aspects of the design that are relevant to the users of
 the library.

 @subsection design-resources Memory and resource handling

 Some VLFeat functions return pointers to memory blocks or
 objects. Only ::vl_malloc, ::vl_calloc, ::vl_realloc, or functions
 whose name contains either the keywords @c new or @c copy,
 transfer the ownership of the memory block or object to the
 caller. The caller must dispose explicitly of all the resources he
 owns (by calling ::vl_free for a memory block, or the appropriate
 destructor for an object).

 The memory allocation functions can be customized by
 ::vl_set_alloc_func (which sets the implementations of ::vl_malloc,
 ::vl_realloc, ::vl_calloc and ::vl_free). Remapping the memory
 allocation functions can be done only if there are no currently
 allocated VLFeat memory blocks or objects. The memory allocation
 functions are common to all threads.

 VLFeat uses three rules that simplify handling exceptions:

 - The library allocates local memory only through the reprogrammable
   ::vl_malloc, ::vl_calloc, and ::vl_realloc functions.

 - The only resource referenced by VLFeat objects is memory (for
   instance, it is illegal for an object to reference an open file).
   Other resources such as files or threads may be allocated within a
   VLFeat function call, but they are all released before the function
   ends, or their ownership is directly transferred to the caller.

 - The global library state is an exception. It cannot reference any
   local object created by the caller and uses the standard C memory
   allocation functions.

 In this way, the VLFeat local state can be reset at any time simply
 by disposing of all the memory allocated so far. The latter can be
 done easily by mapping the memory allocation functions to
 implementations that track the memory blocks allocated, and simply
 disposing of all such blocks. Since the global state does not
 reference any local object nor uses the remapped memory functions, it
 is unaffected by such an operation; conversely, since no VLFeat
 object references anything but memory, this guarantees that all
 allocated resources are properly disposed (no leaks). This is used
 extensively in the design of MATLAB MEX files (see @ref
 design-matlab).

 @subsection design-objects Objects

 Many VLFeat algorithms are availale in the form of
 &ldquo;objects&rdquo;. Notice that the C language, used by VLFeat,
 does not support objects explicitly. Here an object indicates an
 opaque data structure along with a number of functions (methods)
 operationg on it.

 Object names are captilaised and start with the <code>Vl</code>
 prefix (for example ::VlSiftFilt). Object methods are lowercase and
 start with the <code>vl_<object_name>_</code> suffix
 (e.g. ::vl_sift_new). Object methods typraically include a constructor
 (e.g. ::vl_sift_new), a destructor (::vl_sift_delete), some getter
 methods (::vl_sift_get_octave_index), and some setter methods
 (::vl_sift_set_magnif).

 @subsection design-threads Multi-threading

 VLFeat can be used with multiple threads by treating appropriately
 different kinds of operations:

 - <b>Local operations (reentrancy).</b> Most VLFeat operations are
   reentrant, in the sense that they operate on local data. It is safe
   to execute such operations concurrently from multiple threads as
   long as each thread operates on an independent sets of objects or
   memory blocks.  By contrast, operating on the same object or memory
   block from multiple threads requires proper synchronization by the
   user.

 - <b>Task-specific operations.</b> A few operations are intrinsically
   non-reentrant but thread-specific. These include: retrieving the
   last error by ::vl_get_last_error and obtaining the thread-specific
   random number generator by ::vl_get_rand. VLFeat makes such
   operations thread-safe by operating on task-specific data.

 - <b>Global operations.</b> A small number of operations are
   non-reentrant <em>and</em> affect all threads simultaneously. These
   are restricted to changing certain global configuration parameters,
   such as the memory allocation functions by
   ::vl_set_alloc_func. These operations are <em>not</em> thread safe
   and should be executed before multiple threads are started.

 Some VLFeat algorithms are randomised. Each thread has his own random
 number generator (an instance of ::VlRand) accessed by
 ::vl_get_rand. To make calculations reproducible the random number
 generator must be seeded appropriately in each thread. Notice also
 that using the same VLFeat object from multiple threads (with
 appropriate synchronization) will cause multiple random number
 generators to be intermixed.

 @subsection design-portability Portability features

 Platform dependent details are isolated in the @ref host.h
 library module. These include:

 - Atomic types (e.g. ::vl_int32).
 - Special syntaxes for the declaration of symbols exported by the library
   and inline functions (e.g. ::VL_EXPORT).
 - Host-dependent conversion of data endianess
   (e.g. ::vl_swap_host_big_endianness_8()).

 VLFeat uses processor specific features (e.g. Intel SSE) if those are
 available at run time.