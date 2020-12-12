#include "segment-graph.h"

bool operator<(const edge &a, const edge &b) {
  return a.w < b.w;
}

