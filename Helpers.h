/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef HELPERS_H
#define HELPERS_H

// ITK
#include "itkVectorImage.h"

namespace Helpers
{

template <typename TImage, typename TLabelImage>
void ColorLabelsByAverageColor(const TImage* image, const TLabelImage* labelImage, TImage* output);

template <typename TImage>
typename TImage::PixelType MaxValue(const TImage* image);

template<typename TImage>
unsigned int CountPixelsWithValue(const TImage* image, typename TImage::PixelType value);

template<typename TImage