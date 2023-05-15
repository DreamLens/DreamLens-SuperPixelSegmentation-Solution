#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include "itkSLICSegmentation.h"

//typedef itk::Image<itk::CovariantVector<float, 3>, 2> ImageType;
typedef itk::VectorImage<float, 2> ImageType;
typedef itk::Image<int, 2> LabelImageType;

int main(int argc, char* argv[])
{
  typedef itk::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->Se