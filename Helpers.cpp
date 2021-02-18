#include "Helpers.h"

namespace Helpers
{
  
// This is a specialization that ensures that the number of pixels per component also matches.
template<>
void DeepCopy<itk::VectorImage<unsigne