
#include <vl/quickshift.h>

#include <iostream>
#include <set>
#include <vector>

unsigned int ComputeLinearIndex(const unsigned int row, const unsigned int col, const unsigned int width, const unsigned int height, const unsigned int channel);

template <typename T>
std::vector<T> GetVectorFromArray(const T* array, const unsigned int size);

template<typename T>
void OutputMatrix(const T* array, const unsigned int width, const unsigned int height, const unsigned int channels = 1);

template<typename T>
void OutputMatrix(const std::vector<T>& v, const unsigned int width, const unsigned int height, const unsigned int channels = 1);

template<typename T>
void OutputArray(const T* array, const unsigned int length);

template<typename T>
void OutputVector(const std::vector<T>& v);

std::vector<int> GetLabelsFromParents(const std::vector<int>& parents);

bool VectorsIdential(const std::vector<int>& v1, const std::vector<int>& v2);

std::vector<int> SequentialLabels(const std::vector<int>& v);

int main()
{
  unsigned int width = 4;
  unsigned int height = 2;
  unsigned int channels = 3; // This is a color image
  // Create an image with the left half white and the right half black.
  unsigned int totalPixels = width*height;
  std::cout << "totalPixels: " << totalPixels << std::endl;
  
  vl_qs_type* image = new vl_qs_type[totalPixels*channels];
  
  vl_qs_type ratio = 10.0f;
  for(unsigned int channel = 0; channel < channels; ++channel)
    {
    for (unsigned int y = 0 ; y < height ; ++y)
      {
      for (unsigned int x = 0  ; x < width ; ++x) 
        {
        unsigned int linearIndex = ComputeLinearIndex(y, x, width, height, channel);
        std::cout << "linearIndex: " << linearIndex << std::endl;