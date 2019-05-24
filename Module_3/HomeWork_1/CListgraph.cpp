#include "CListGraph.h"

CListGraph::CListGraph(unsigned int v_count) : count(v_count), in(count), out(count) {}

CListGraph::CListGraph(const IGraph *graph) : count(graph->VerticesCount()), in(count), out(count) {
  std::vector<int> nodes;

  for (int i = 0; i < count; i++) {
    nodes = graph->GetNextVertices(i);
    for (auto &j : nodes) {
      AddEdge(i, j);
    }
  }
}

void CListGraph::AddEdge(int from, int to) {
  in[to].push_back(from);
  out[from].push_back(to);
}

int CListGraph::VerticesCount() const {
  return count;
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : out[vertex]) {
    result.push_back(i);
  }

  return result;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;

  for (auto &i : in[vertex]) {
    result.push_back(i);
  }

  return result;
}