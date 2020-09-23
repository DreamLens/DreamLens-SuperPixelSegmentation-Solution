#include "imconv.h"

image<uchar> *imageRGBtoGRAY(image<rgb> *input) {
  int width = input->width();
  int height = input->height();
  image<uc