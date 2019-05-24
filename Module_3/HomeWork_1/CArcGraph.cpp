#include "CArcGraph.h"

CArcGraph::Edge::Edge(int from, int to) : from(from), to(to) {}

CArcGraph::CArcGraph(unsigned int v_count) : count(v_count) {}

CArcGraph::CArcGraph(const IGraph *graph) : count(graph->VerticesCount()) {
  std::vector<int> nodes;
  for (int i = 0; i < count; i++) {
    nodes = graph->GetNextVertices(i);
    for (auto &j : nodes) {
      AddEdge(i, j);
    }
  }
}

void CArcGraph::AddEdge(int from, int to) {
  Edge edge(from, to);
  edges.push_back(edge);
}

int CArcGraph::VerticesCount() const {
  return count;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : edges)
    if (i.from == vertex)
      result.push_back(i.to);

  return result;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : edges)
    if (i.to == vertex)
      result.push_back(i.from);

  return result;
}