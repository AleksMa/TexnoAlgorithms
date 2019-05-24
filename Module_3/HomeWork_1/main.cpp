#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"

int main() {
  size_t count_node = 0;
  size_t count_edge = 0;
  std::cin >> count_node >> count_edge;
  CListGraph graph(count_node);

  int from = 0;
  int to = 0;
  for (size_t i = 0; i < count_edge; i++) {
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }
  for (size_t i = 0; i < graph.VerticesCount(); i++) {
    std::cout << i << ": ";
    for (auto &j : graph.GetNextVertices(i)) {
      std::cout << j << ' ';
    }
    std::cout << std::endl;
  }

  char type_graph;
  IGraph *new_graph;
  std::cin >> type_graph;
  switch (type_graph) {
    case 'l':new_graph = new CListGraph(&graph);
      break;
    case 'm':new_graph = new CMatrixGraph(&graph);
      break;
    case 's':new_graph = new CSetGraph(&graph);
      break;
    case 'a':new_graph = new CArcGraph(&graph);
      break;
    default:return 0;

  }

  std::cout << "Count vertices:" << new_graph->VerticesCount() << std::endl;

  std::cout << "Next vertices:\n";
  for (size_t i = 0; i < new_graph->VerticesCount(); i++) {
    std::cout << i << ": ";
    for (auto &j : new_graph->GetNextVertices(i)) {
      std::cout << j << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << "Prev vertices:\n";
  for (size_t i = 0; i < new_graph->VerticesCount(); i++) {
    std::cout << i << ": ";
    for (auto &j : new_graph->GetPrevVertices(i)) {
      std::cout << j << ' ';
    }
    std::cout << std::endl;
  }

  delete new_graph;

  return 0;
}