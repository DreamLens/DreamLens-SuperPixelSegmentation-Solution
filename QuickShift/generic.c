
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