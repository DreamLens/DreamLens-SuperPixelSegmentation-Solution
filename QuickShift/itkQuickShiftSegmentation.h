#ifndef __itkQuickShiftSegmentation_h
#define __itkQuickShiftSegmentation_h

#include "itkImageToImageFilter.h"

namespace itk
{
template< typename TInputImage, typename TOutputLabelImage>
class QuickShiftSegmentation : public ImageToImageFilter<TInputImage, TOutputLabelImage>
{
public:
  /** Standard class typedefs. */
  typedef QuickShiftSegmentation Self;
  typedef ImageToImageFilter<TInp