#include "CSetGraph.h"

CSetGraph::CSetGraph(unsigned int count) : count(count), in(count), out(count) {}

CSetGraph::CSetGraph(const IGraph *graph) : count(graph->VerticesCount()), in(count), out(count) {
  std::vector<int> nodes;

  for (int i = 0; i < count; i++) {
    nodes = graph->GetNextVertices(i);
    for (auto &j : nodes) {
      AddEdge(i, j);
    }
  }
}

void CSetGraph::AddEdge(int from, int to) {
  in[to].insert(from);
  out[from].insert(to);
}

int CSetGraph::VerticesCount() const { return count; }

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : out[vertex]) {
    result.push_back(i);
  }

  return result;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : in[vertex]) {
    result.push_back(i);
  }

  return result;
}