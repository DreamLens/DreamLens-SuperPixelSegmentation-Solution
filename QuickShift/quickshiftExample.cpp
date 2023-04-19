#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileWriter.h"

#include "itkQuickShiftSegmentation.h"

typedef itk::VectorImage<unsigned char, 2> ImageType;
typedef itk::Image<unsigned int, 2> LabelImageType;

template<typename TImage>
static void CreateImage(TImage* image);

template<typ