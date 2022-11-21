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
shift. The algorithm segments a color image (or any