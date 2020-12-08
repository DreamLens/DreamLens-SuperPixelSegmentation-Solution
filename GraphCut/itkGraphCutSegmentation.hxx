
#ifndef __itkGraphCutSegmentation_txx
#define __itkGraphCutSegmentation_txx

#include "itkGraphCutSegmentation.h"

// Custom
#include "Helpers.h"

// ITK
#include "itkBilateralImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkObjectFactory.h"

// Segmentation
#include "image.h" // The image class for the segmentation algorithm
#include "misc.h" // Defines the 'rgb' type.
#include "segment-image.h"

namespace itk
{

template< typename TInputImage, typename TOutputLabelImage>
GraphCutSegmentation< TInputImage, TOutputLabelImage>
::GraphCutSegmentation() : m_MinSize(20), m_K(500), m_Sigma(2.0)
{
  this->SetNumberOfRequiredOutputs(2);

  this->SetNthOutput( 0, this->MakeOutput(0) );
  this->SetNthOutput( 1, this->MakeOutput(1) );
}

template< typename TInputImage, typename TOutputLabelImage>
DataObject::Pointer GraphCutSegmentation<TInputImage, TOutputLabelImage>::MakeOutput(unsigned int idx)
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
TOutputLabelImage* GraphCutSegmentation<TInputImage, TOutputLabelImage>::GetLabelImage()
{
  return dynamic_cast< TOutputLabelImage * >(this->ProcessObject::GetOutput(0) );
}

template< typename TInputImage, typename TOutputLabelImage>
TInputImage* GraphCutSegmentation<TInputImage, TOutputLabelImage>::GetColoredImage()
{
  return dynamic_cast< TInputImage * >(this->ProcessObject::GetOutput(1) );
}

template< typename TInputImage, typename TOutputLabelImage>
void GraphCutSegmentation< TInputImage, TOutputLabelImage>
::GenerateData()
{
  typename TInputImage::ConstPointer filterInput = this->GetInput();
  
  typename TInputImage::Pointer input;
  if(!this->m_BlurFirst)
    {
    input = const_cast<TInputImage*>(filterInput.GetPointer());
    }
  else
    {
    // Optionally blur
//     typedef itk::BilateralImageFilter<TInputImage, TInputImage>  BilateralImageFilterType;
//     BilateralImageFilterType::Pointer bilateralImageFilter = BilateralImageFilterType::New();
//     bilateralImageFilter->SetInput(filterInput);
//     bilateralImageFilter->SetDomainSigma(domainSigma);
//     bilateralImageFilter->SetRangeSigma(rangeSigma);
//     bilateralImageFilter->Update();
//    input = bilateralImageFilter->GetOutput();
    float domainSigma = 3.0f;
    float rangeSigma = 10.0f;
    //Helpers::BilateralAllChannels<TInputImage>(filterInput, input, domainSigma, rangeSigma);
    Helpers::BilateralAllChannels<TInputImage>(const_cast<TInputImage*>(filterInput.GetPointer()), input, domainSigma, rangeSigma);

    }

  Helpers::WriteImage<TInputImage>(input, "finalInput.mha");
