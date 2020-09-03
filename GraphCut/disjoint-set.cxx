#include "disjoint-set.h"

universe::universe(int elements) {
  elts = new uni_elt[elements];
  num = elements;