#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkJPEGWriter.h>

#include "vtkSuperPixelSegmentation.h"

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkJPEGReader> reader = 
      vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();
  
  vtkSmartPointer<vtkSuperPixelSegmentation> superPixelSegmentation = 
      vtkSmartPointer<vtkSuperPixelSegmentation>::New();

  superPixelSegment