#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkJPEGWriter.h>

#include "vtkSuperPixelSegmentation.h"

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkJPEGReader> reader = 
      vtkSmartPointer<