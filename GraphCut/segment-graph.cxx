#include "segment-graph.h"

bool operator<(const edge &a, const edge &b) {
  return a.w < b.w;
}

universe *segment_graph(int num_vertices, int num_edges, edge *edges, 
			float c) { 
  // sort edges by weigh