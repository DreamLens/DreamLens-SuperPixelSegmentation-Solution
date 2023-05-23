
#ifndef __itkSLICSegmentation_txx
#define __itkSLICSegmentation_txx

#include "itkSLICSegmentation.h"

// Custom
#include "Helpers.h"

// ITK
#include "itkBilateralImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkObjectFactory.h"

// Segmentation
#include "SLIC.h"

namespace itk
{

template< typename TInputImage, typename TOutputLabelImage>
SLICSegmentation< TInputImage, TOutputLabelImage>
::SLICSegmentation() : m_NumberOfSuperPixels(200), m_SpatialDistanceWeight(5.0)
{
  this->SetNumberOfRequiredOutputs(3);

  this->SetNthOutput( 0, this->MakeOutput(0) );
  this->SetNthOutput( 1, this->MakeOutput(1) );
  this->SetNthOutput( 2, this->MakeOutput(2) );
}

template< typename TInputImage, typename TOutputLabelImage>
DataObject::Pointer SLICSegmentation<TInputImage, TOutputLabelImage>::MakeOutput(unsigned int idx)
{
  DataObject::Pointer output;

  switch ( idx )
    {
    case 0:
      output = ( TOutputLabelImage::New() ).GetPointer(); // The output for the label image
      break;
    case 1:
      output = ( TInputImage::New() ).GetPointer(); // The output for the image colored by the average color in each region
      break;
    case 2:
      output = ( TInputImage::New() ).GetPointer(); // The output for the image with the segment boundaries drawn on it
      break;
    default:
      std::cerr << "No output " << idx << std::endl;
      output = NULL;
      break;
    }
  return output.GetPointer();
}

template< typename TInputImage, typename TOutputLabelImage>
TOutputLabelImage* SLICSegmentation<TInputImage, TOutputLabelImage>::GetLabelImage()
{
  return dynamic_cast< TOutputLabelImage * >(this->ProcessObject::GetOutput(0) );
}

template< typename TInputImage, typename TOutputLabelImage>
TInputImage* SLICSegmentation<TInputImage, TOutputLabelImage>::GetContourImage()
{
  return dynamic_cast< TInputImage * >(this->ProcessObject::GetOutput(1) );
}

template< typename TInputImage, typename TOutputLabelImage>
TInputImage* SLICSegmentation<TInputImage, TOutputLabelImage>::GetColoredImage()
{
  return dynamic_cast< TInputImage * >(this->ProcessObject::GetOutput(2) );
}

template< typename TInputImage, typename TOutputLabelImage>
void SLICSegmentation< TInputImage, TOutputLabelImage>
::GenerateData()
{
  TInputImage* input = const_cast<TInputImage*>(this->GetInput());

  // The SLIC implementation expects RGB values packed into int pixels.
  typedef itk::Image<unsigned int, 2> UnsignedIntImageType;
  UnsignedIntImageType::Pointer image = UnsignedIntImageType::New();
  image->SetRegions(input->GetLargestPossibleRegion());
  image->Allocate();

  itk::ImageRegionIterator<TInputImage> imageIterator(input, input->GetLargestPossibleRegion());

  while(!imageIterator.IsAtEnd())
    {
    int intPixel = PACK(1, imageIterator.Get()[0], imageIterator.Get()[1], imageIterator.Get()[2]);
    image->SetPixel(imageIterator.GetIndex(), intPixel);
 
    ++imageIterator;
    }

  //WriteImage<UnsignedIntImageType>(image, "input4channel.mha");

  unsigned int width = image->GetLargestPossibleRegion().GetSize()[0];
  unsigned int height = image->GetLargestPossibleRegion().GetSize()[1];

  int numberOfPixels = width*height;

  this->Labels = new int[numberOfPixels];
  int numlabels(0);
  SLIC slic;
  
  slic.DoSuperpixelSegmentation_ForGivenK(image->GetBufferPointer(), width, height, this->Labels, numlabels, m_NumberOfSuperPixels, m_SpatialDistanceWeight);
  
  typename TOutputLabelImage::Pointer outputLabelImage = this->GetLabelImage(); // One of the output ports
  outputLabelImage->SetRegions(image->GetLargestPossibleRegion());
  outputLabelImage->Allocate();
  
  itk::ImageRegionIterator<TOutputLabelImage> labelIterator(outputLabelImage, outputLabelImage->GetLargestPossibleRegion());
 