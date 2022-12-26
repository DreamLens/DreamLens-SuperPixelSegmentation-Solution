/** @internal
 ** @file     quickshift.c
 ** @author   Brian Fulkerson
 ** @author   Andrea Vedaldi
 ** @brief    Quick shift image segmentation - Definition
 **/

/* AUTORIGHTS
Copyright (C) 2007-10 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

/** 

@file   quickshift.h
@author Brian Fulkerson
@author Andrea Vedaldi
@brief  Quick shift image segmentation

- @ref quickshift-intro
- @ref quickshift-usage
- @ref quickshift-tech

@section quickshift-intro Overview

Quick shift [1] is a fast mode seeking algorithm, similar to mean
shift. The algorithm segments a color image (or any image with more
than one component) by identifying clusters of pixels in the joint
spatial and color dimensions. Segments are local (superpixels) and can
be used as a basis for further processing.

Given an image, the algorithm calculates a forest of pixels whose
branches are labeled with a distance value
(::vl_quickshift_get_parents, ::vl_quickshift_get_dists). This
specifies a hierarchical segmentation of the image, with segments
corresponding to subtrees. Useful superpixels can be identified by
cutting the branches whose distance label is above a given threshold
(the threshold can be either fixed by hand, or determined by cross
validation).

Parameter influencing the algorithm are:

- <b>Kernel size.</b> The pixel density and its modes are
estimated by using a Parzen window estimator with a Gaussian kernel of
the specified size (::vl_quickshift_set_kernel_size). The larger the
size, the larger the neighborhoods of pixels considered.
- <b>Maximum distance.</b> This (::vl_quickshift_set_max_dist) is the maximum
distance between two pixels that the algorithm considers when building
the forest. In principle, it can be infinity (so that a tree is
returned), but in practice it is much faster to consider only
relatively small distances (the maximum distance can be set to a small
multiple of the kernel size).

[1] A. Vedaldi and S. Soatto. &ldquo;Quick Shift and Kernel Methods
for Mode Seeking&rdquo;, in <em>Proc. ECCV</em>, 2008.

@section quickshift-usage Usage

- Create a new quick shift object (::vl_quickshift_new). The object
  can be reused for multiple images of the same size.
- Configure quick shift by setting the kernel size
  (::vl_quickshift_set_kernel_size) and the maximum gap
  (::vl_quickshift_set_max_dist). The latter is in principle not
  necessary, but useful to speedup processing.
- Process an image (::vl_quickshift_process).
- Retrieve the parents (::vl_quickshift_get_parents) and the distances
  (::vl_quickshift_get_dists). These can be used to segment
  the image in superpixels.
- Delete the quick shift object (::vl_quickshift_delete).

@section quickshift-tech Technical details

For each pixel <em>(x,y)</em>, quick shift regards @f$ (x,y,I(x,y))
@f$ as a sample from a <em>d + 2</em> dimensional vector space. It
then calculates the Parzen density estimate (with a Gaussian kernel of
standard deviation @f$ \sigma @f$)

@f[
E(x,y) = P(x,y,I(x,y)) = \sum_{x'y'} 
\frac{1}{(2\pi\sigma)^{d+2}}
\exp
\left(
-\frac{1}{2\sigma^2} 
\left[
\begin{array}{c}
x - x' \\
y - y' \\
I(x,y) - I(x',y') \\
\end{array}
\right] 
\right)
@f]

Then quick shift construct a tree connecting each image pixel to its
nearest neighbor which has greater density value. Formally, write @f$
(x',y') >_P (x,y) @f$ if, and only if,

@f[
  P(x',y',I(x',y')) > P(x,y,I(x,y))}.
@f]

Each pixel <em>(x, y)</em> is connected to the closest higher density
pixel <em>parent(x, y)</em> that achieves the minimum distance in

@f[
 \mathrm{dist}(x,y) = 
 \mathrm{min}_{(x',y') > P(x,y)}
\left(
(x - x')^2 +
(y - y')^2 +
\| I(x,y) - I(x',y') \|_2^2 
\right).
@f]

    
**/
  
#include "quickshift.h"
#include "mathop.h"

#include <string.h>
#include <math.h>
#include <stdio.h>


/** -----------------------------------------------------------------
 ** @internal
 ** @brief Computes the accumulated channel L2 distance between
 **        i,j + the distance between i,j
 **
 ** @param I    input image buffer
 ** @param N1   size of the first dimension of the image
 ** @param N2   size