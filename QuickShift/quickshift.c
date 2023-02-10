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
 ** @param N2   size of the second dimension of the image
 ** @param K    number of channels
 ** @param i1   first dimension index of the first pixel to compare
 ** @param i2   second dimension of the first pixel
 ** @param j1   index of the second pixel to compare
 ** @param j2   second dimension of the second pixel
 **
 ** Takes the L2 distance between the values in I at pixel i and j, 
 ** accumulating along K channels and adding in the distance
 ** between i,j in the image.
 ** 
 ** @return the distance as described above
 **/

VL_INLINE
vl_qs_type
vl_quickshift_distance(vl_qs_type const * I, 
         int N1, int N2, int K,
         int i1, int i2,
         int j1, int j2) 
{
  vl_qs_type dist = 0 ;
  int d1 = j1 - i1 ;
  int d2 = j2 - i2 ;
  int k ;
  dist += d1*d1 + d2*d2 ;
  /* For k = 0...K-1, d+= L2 distance between I(i1,i2,k) and 
   * I(j1,j2,k) */
  for (k = 0 ; k < K ; ++k) {
    vl_qs_type d = 
      I [i1 + N1 * i2 + (N1*N2) * k] - 
      I [j1 + N1 * j2 + (N1*N2) * k] ;
    dist += d*d ;
  }
  return dist ;
}

/** -----------------------------------------------------------------
 ** @internal
 ** @brief Computes the accumulated channel inner product between i,j + the
 **        distance between i,j
 ** 
 ** @param I    input image buffer
 ** @param N1   size of the first dimension of the image
 ** @param N2   size of the second dimension of the image
 ** @param K    number of channels
 ** @param i1   first dimension index of the first pixel to compare
 ** @param i2   second dimension of the first pixel
 ** @param j1   index of the second pixel to compare
 ** @param j2   second dimension of the second pixel
 **
 ** Takes the channel-wise inner product between the values in I at
 ** pixel i and j, accumulating along K channels and adding in the
 ** inner product between i,j in the image.
 ** 
 ** @return the inner product as described above
 **/

VL_INLINE
vl_qs_type
vl_quickshift_inner(vl_qs_type const * I, 
      int N1, int N2, int K,
      int i1, int i2,
      int j1, int j2) 
{
  vl_qs_type ker = 0 ;
  int k ;
  ker += i1*j1 + i2*j2 ;
  for (k = 0 ; k < K ; ++k) {
    ker += 
      I [i1 + N1 * i2 + (N1*N2) * k] *
      I [j1 + N1 * j2 + (N1*N2) * k] ;
  }
  return ker ;
}

/** -----------------------------------------------------------------
 ** @brief Create a quick shift object
 ** @param image
 ** @param height
 ** @param width
 ** @param channels
 **
 ** @return New quick shift object.
 **/
 
VL_EXPORT
VlQS *
vl_quickshift_new(vl_qs_type const * image, int height, int width,
                       int channels)
{
  VlQS * q = vl_malloc(sizeof(VlQS));

  q->image    = (vl_qs_type *)image;
  q->height   = height;
  q->width    = width;
  q->channels = channels;

  q->medoid   = VL_FALSE;
  q->tau      = VL_MAX(height,width)/50;
  q->sigma    = VL_MAX(2, q->tau/3);

  q->dists    = vl_calloc(height*width, sizeof(vl_qs_type));
  q->parents  = vl_calloc(height*width, sizeof(int)); 
  q->density  = vl_calloc(height*width, sizeof(vl_qs_type)) ;

  return q;
}

/** -----------------------------------------------------------------
 ** @brief Create a quick shift objet
 ** @param q quick shift object.
 **/

VL_EXPORT
void vl_quickshift_process(VlQS * q)
{
  vl_qs_type c