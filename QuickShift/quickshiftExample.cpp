#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileWriter.h"

#include "itkQuickShiftSegmentation.h"

typedef itk::VectorImage<unsigned char, 2> ImageType;
typedef itk::Image<unsigned int, 2> LabelImageType;

template<typename TImage>
static void CreateImage(TImage* image);

template<typename TImage>
static void WriteImage(TImage* image, const std::string& filename);

int main()
{
  ImageType::Pointer image = ImageType::New();
  CreateImage<ImageType>(image);

  typedef itk::QuickShiftSegmentation<ImageType, LabelImageType> QuickShiftSegmentationType;
  QuickShiftSegmentationType::Pointer quickShiftSegmentation = QuickShiftSegmentationType::New();

  return 0;
}


template<typename TImage>
void CreateImage(TImage* image)
{
  itk::Index<2> start;
  start.Fill(0);
 
  itk::Size<2> size;
  size.Fill(5);
 
  itk::ImageRegion<2> region(start,siz