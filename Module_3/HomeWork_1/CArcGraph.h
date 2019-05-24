#ifndef CARCGRAPH_H
#define CARCGRAPH_H

#include <iostream>
#include "IGraph.h"

class CArcGraph : public IGraph {
 public:
  CArcGraph(unsigned int v_count);
  CArcGraph(const IGraph *graph);

  virtual void AddEdge(int from, int to) override;
  virtual int VerticesCount() const override;
  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;

 private:

  struct Edge {
    Edge(int from, int to);

    int from;
    int to;
  };

  size_t count;
  std::vector<Edge> edges;

};

#endif //CARCGRAPH_H
