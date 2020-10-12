#include "imconv.h"

image<uchar> *imageRGBtoGRAY(image<rgb> *input) {
  int width = input->width();
  int height = input->height();
  image<uchar> *output = new image<uchar>(width, height, false);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      imRef(output, x, y) = (uchar)
	(imRef(input, x, y).r * RED_WEIGHT +
	 imRef(input, x, y).g * GREEN_WEIGHT +
	 imRef(input, x, y).b * BLUE_WEIGHT);
    }
  }
  return output;
}

image<rgb> *imageGRAYtoRGB(image<uchar> *input) {
  int width = input->width();
  int height = input->height();
  image<rgb> *output = new image<rgb>(width, height, false);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      imRef(output, x, y).r = imRef(input, x, y);
      imRef(output, x, y).g = imRef(input, x, y);
      imRef(output, x, y).b = imRef(input, x, y);
    }
  }
  return output;  
}

image<float> *imageUCHARtoFLOAT(image<uchar> *input) {
  int width = input->width();
  int height = input->height();
  image<float> *output = new image<float>(width, height, false);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      imRef(output, x, y) = imRef(input, x, y);
    }
  }
  return output;  
}

image<float> *imageINTtoFLOAT(image<int> *input) {
  int width = input->width();
  int height = input->height();
  image<float> *output = new image<float>(width, height, false);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      imRef(output, x, y) = imRef(input, x, y);
    }
  }
  return output;  
}

image<uchar> *imageFLOATtoUCHAR(image<float> *input, 
				       float min, float max) {
  int width = input->width();
  int height = input->height();
  image<uchar> *output = new image<uchar>(width, height, false);

  if (max == min)
    return output;

  float scale = UCHAR_MAX / (max - min);
 