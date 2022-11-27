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