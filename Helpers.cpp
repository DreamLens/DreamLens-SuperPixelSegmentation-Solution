#include "Helpers.h"

namespace Helpers
{
  
// This is a specialization that ensures that the number of pixels per component also matches.
template<>
void DeepCopy<itk::VectorImage<unsigned char, 2> >(const itk::VectorImage<unsigned char, 2>* input, itk::VectorImage<unsigned char, 2>* output)
{
  //std::cout << "DeepCopy<FloatVectorImageType>()" << std::endl;
  bool changed = false;
  if(inpu