#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(unsigned int v_count) :
    count(v_count),
    edges(v_count, std::vector<int>(v_count, 0)) {}

CMatrixGraph::CMatrixGraph(const IGraph *graph) :
    count(graph->VerticesCount()),
    edges(count, std::vector<int>(count, 0)) {
  std::vector<int> nodes;
  for (int i = 0; i < count; i++) {
    nodes = graph->GetNextVertices(i);
    for (auto &j : nodes) {
      AddEdge(i, j);
    }
  }
}

void CMatrixGraph::AddEdge(int from, int to) {
  edges[from][to]++;
}

int CMatrixGraph::VerticesCount() const {
  return count;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;

  for (int i = 0; i < count; i++) {
    if (edges[vertex][i]) {
      auto iter = result.cend();
      result.insert(iter, edges[vertex][i], i);
    }
  }
  return result;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;

  for (int i = 0; i < count; i++) {
    if (edges[i][vertex]) {
      auto iter = result.cend();
      result.insert(iter, edges[i][vertex], i);
    }
  }

  return result;
}