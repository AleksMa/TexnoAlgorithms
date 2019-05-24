#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H

#include <iostream>
#include "IGraph.h"

class CMatrixGraph : public IGraph {
 public:
  CMatrixGraph(unsigned int v_count);
  CMatrixGraph(const IGraph *graph);

  virtual void AddEdge(int from, int to) override;
  virtual int VerticesCount() const override;
  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  size_t count;
  std::vector<std::vector<int>> edges;
};

#endif //CMATRIXGRAPH_H
