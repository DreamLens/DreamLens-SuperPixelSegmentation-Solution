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

  superPixelSegmentation->SetSigma(.5);
  superPixelSegmentation->SetK(500);
  superPixelSegmentation->SetMinSize(50);
    
  superPixelSegmentation->SetInputConnection(reader->GetOutputPort());
  superPixelSegmentati