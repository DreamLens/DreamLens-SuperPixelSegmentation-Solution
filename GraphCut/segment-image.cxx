#include "segment-image.h"

rgb random_rgb()
{ 
  rgb c;
  double r;
  
  c.r = (uchar)random();
  c.g = (uchar)random();
  c.b = (uchar)random();

  return c;
}

image<int> *segment_image(image<rgb> *im, float c, int min_size, int *num_ccs) {
  int width = im->width();
  int height = im->height()