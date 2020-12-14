#include "segment-graph.h"

bool operator<(const edge &a, const edge &b) {
  return a.w < b.w;
}

universe *segment_graph(int num_vertices, int num_edges, edge *edges, 
			float c) { 
  // sort edges by weight
  std::sort(edges, edges + num_edges);

  // make a disjoint-set forest
  universe *u = new universe(num_vertices);

  // init thresholds
  float *threshold = new float[num_vertices];
  for (int i = 0; i < num_vertice