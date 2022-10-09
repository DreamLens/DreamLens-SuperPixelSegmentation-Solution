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
  typedef ImageToImageFilter<TInputImage, TOutputLabelImage> Superclass;
  typedef SmartPointer< Self >        Pointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(QuickShiftSegmentation, ImageToImageFilter);

  // The approximate number of superpixels in the result.
  itkSetMacro( KernelSize, float);
  itkGetMacro( KernelSize, float);

  // Maximum distance between two pixels in the same label.
  itkSetMacro( MaxDist, float );
  itkGetMacro( MaxDist, float);
  
  // Tradeoff between color and distance. Larger values give more importance to c