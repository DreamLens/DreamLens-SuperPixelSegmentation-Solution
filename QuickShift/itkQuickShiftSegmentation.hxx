
#ifndef __itkQuickShiftSegmentation_txx
#define __itkQuickShiftSegmentation_txx

#include "itkQuickShiftSegmentation.h"

// Custom
#include "Helpers.h"

// ITK
#include "itkBilateralImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkObjectFactory.h"

// Segmentation
#include "quickshift.h"

namespace itk
{

template< typename TInputImage, typename TOutputLabelImage>
QuickShiftSegmentation< TInputImage, TOutputLabelImage>
::QuickShiftSegmentation() : m_KernelSize(5), m_MaxDist(10.0)
{
  this->SetNumberOfRequiredOutputs(2);

  this->SetNthOutput( 0, this->MakeOutput(0) );
  this->SetNthOutput( 1, this->MakeOutput(1) );
}

template< typename TInputImage, typename TOutputLabelImage>
DataObject::Pointer QuickShiftSegmentation<TInputImage, TOutputLabelImage>::MakeOutput(unsigned int idx)
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
    default:
      std::cerr << "No output " << idx << std::endl;
      output = NULL;
      break;
    }
  return output.GetPointer();
}

template< typename TInputImage, typename TOutputLabelImage>
TOutputLabelImage* QuickShiftSegmentation<TInputImage, TOutputLabelImage>::GetLabelImage()
{
  return dynamic_cast< TOutputLabelImage * >(this->ProcessObject::GetOutput(0) );
}

template< typename TInputImage, typename TOutputLabelImage>
TInputImage* QuickShiftSegmentation<TInputImage, TOutputLabelImage>::GetColoredImage()
{
  return dynamic_cast< TInputImage * >(this->ProcessObject::GetOutput(1) );
}

template< typename TInputImage, typename TOutputLabelImage>
void QuickShiftSegmentation< TInputImage, TOutputLabelImage>
::GenerateData()
{
  TInputImage* input = const_cast<TInputImage*>(this->GetInput());

  unsigned int width = input->GetLargestPossibleRegion().GetSize()[0];
  unsigned int height = input->GetLargestPossibleRegion().GetSize()[1];
  unsigned int channels = input->GetNumberOfComponentsPerPixel();
  
  unsigned int totalPixels = width*height;
  
  vl_qs_type* image = new vl_qs_type[totalPixels*channels];
  
  itk::ImageRegionIterator<TInputImage> inputIterator(input, input->GetLargestPossibleRegion());

  while(!inputIterator.IsAtEnd())
    {
    for (unsigned int component = 0; component < input->GetNumberOfComponentsPerPixel(); ++component) 
      {
      unsigned int linearIndex = ComputeLinearValueIndex(inputIterator.GetIndex()[1], inputIterator.GetIndex()[0], width, height, component);
      //std::cout << "linearIndex: " << linearIndex << std::endl;
      //float noise = 255.0f * drand48();
      image[linearIndex] = inputIterator.Get()[component] * this->m_Ratio;
      }
    ++inputIterator;
    }

  // Create a new quick shift object
  VlQS* quickshift = vl_quickshift_new(image, height, width, channels);

  // Configure quick shift by setting the kernel size (vl_quickshift_set_kernel_size)
  // and the maximum gap (vl_quickshift_set_max_dist).
  // The latter is in principle not necessary, but useful to speedup processing.
  std::cout << "vl_quickshift kernel: " << m_KernelSize << " dist: " << m_MaxDist << std::endl;
  vl_quickshift_set_kernel_size(quickshift, this->m_KernelSize);

  vl_quickshift_set_max_dist(quickshift, this->m_MaxDist);

  vl_quickshift_process(quickshift);
  std::cout << "Finished processing." << std::endl;