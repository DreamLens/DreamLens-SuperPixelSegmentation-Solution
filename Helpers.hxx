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

// ITK
#include "itkRegionOfInterestImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkBilateralImageFilter.h"

// STL
#include <set>

namespace Helpers
{

template<typename TImage>
void DeepCopy(const TImage* input, TImage* output)
{
  DeepCopyInRegion<TImage>(input, input->GetLargestPossibleRegion(), output);
}

template<typename TImage>
void DeepCopyInRegion(const TImage* input, const itk::ImageRegion<2>& region, TImage* output)
{
  output->SetRegions(region);
  output->Allocate();

  itk::ImageRegionConstIterator<TImage> inputIterator(input, input->GetLargestPossibleRegion());
  itk::ImageRegionIterator<TImage> outputIterator(output, output->GetLargestPossibleRegion());

  while(!inputIterator.IsAtEnd())
    {
    outputIterator.Set(inputIterator.Get());
    ++inputIterator;
    ++outputIterator;
    }
}


template <class T>
void WriteScaledScalarImage(const typename T::Pointer image, const std::string& filename)
{
  if(T::PixelType::Dimension > 1)
    {
    std::cerr << "Cannot write scaled scalar image with vector image input!" << std::endl;
    return;
    }
  typedef itk::Image<unsigned char, 2> UnsignedCharScalarImageType;
  typedef itk::RescaleIntensityImageFilter<T, UnsignedCharScalarImageType> RescaleFilterType; // expected ';' before rescaleFilter

  typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(image);
  rescaleFilter->SetOutputMinimum(0);
  rescaleFilter->SetOutputMaximum(255);
  rescaleFilter->Update();

  typedef itk::ImageFileWriter<UnsignedCharScalarImageType> WriterType;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(filename);
  writer->SetInput(rescaleFilter->GetOutput());
  writer->Update();
}


template<typename TImage>
void WriteImage(const TImage* image, const std::string& filename)
{
  // This is a convenience function so that images can be written in 1 line instead of 4.
  typename itk::ImageFileWriter<TImage>::Pointer writer = itk::ImageFileWriter<TImage>::New();
  writer->SetFileName(filename);
  writer->SetInput(image);
  writer->Update();
}


template<typename TImage>
void WriteRGBImage(const TImage* input, const std::string& filename)
{
  typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> RGBImageType;

  RGBImageType::Pointer output = RGBImageType::New();
  output->SetRegions(input->GetLargestPossibleRegion());
  output->Allocate();

  itk::ImageRegionConstIterator<TImage> inputIterator(input, input->GetLargestPossibleRegion());
  itk::ImageRegionIterator<RGBImageType> outputIterator(output, output->GetLargestPossibleRegion());

  while(!inputIterator.IsAtEnd())
    {
    itk::CovariantVector<unsigned char, 3> pixel;
    for(unsigned int i = 0; i < 3; ++i)
      {
      pixel[i] = inputIterator.Get()[i];
      }
    outputIterator.Set(pixel);
    ++inputIterator;
    ++outputIterator;
    }

  typename itk::ImageFileWriter<RGBImageType>::Pointer writer = itk::ImageFileWriter<RGBImageType>::New();
  writer->SetFileName(filename);
  writer->SetInput(output);
  writer->Update();

}

template<typename TImage>
void WriteRegion(const typename TImage::Pointer image, const itk::ImageRegion<2>& region, const std::string& filename)
{
  //std::cout << "WriteRegion() " << filename << std::endl;
  //std::cout << "region " << region << std::endl;
  typedef itk::RegionOfInterestImageFilter<TImage, TImage> RegionOfInterestImageFilterType;

  typename RegionOfInterestImageFilterType::Pointer regionOfInterestImageFilter = RegionOfInterestImageFilterType::New();
  regionOfInterestImageFilter->SetRegionOfInterest(region);
  regionOfInterestImageFilter->SetInput(image);
  regionOfInterestImageFilter->Update();

  //std::cout << "regionOfInterestImageFilter " << regionOfInterestImageFilter->GetOutput()->GetLargestPossibleRegion() << std::endl;
  
  typename itk::ImageFileWriter<TImage>::Pointer writer = itk::ImageFileWriter<TImage>::New();
  writer->SetFileName(filename);
  writer->SetInput(regionOfInterestImageFilter->GetOutput());
  writer->Update();
}

template<typename TImage>
void RelabelSequential(typename TImage::Pointer input, typename TImage::Pointer output)
{
  output->SetRegions(input->GetLargestPossibleRegion());
  output->Allocate();

  // Keep only unique label ids
  std::set<typename TImage::PixelType> uniqueLabels;
  itk::ImageRegionConstIterator<TImage> imageIterator(input, input->GetLargestPossibleRegion());

  while(!imageIterator.IsAtEnd())
    {
    uniqueLabels.insert(imageIterator.Get());
    ++imageIterator;
    }

  // Copy the set into a vector to induce an ordering
  std::vector<typename TImage::PixelType> sequentialLabels;
  for(typename std::set<typename TImage::PixelType>::iterator iterator = uniqueLabels.begin(); iterator != uniqueLabels.end(); iterator++)
    {
    sequentialLabels.push_back(*iterator);
    }

  std::map <typename TImage::PixelType, typename TImage::PixelType> labelMap;
  for(unsigned int i = 0; i < sequentialLabels.size(