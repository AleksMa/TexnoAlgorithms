#ifndef CSETGRAPH_H
#define CSETGRAPH_H

#include <iostream>
#include <unordered_set>
#include "IGraph.h"

class CSetGraph : public IGraph {
 public:
  CSetGraph(unsigned int count);
  CSetGraph(const IGraph *graph);

  virtual void AddEdge(int from, int to) override;
  virtual int VerticesCount() const override;
  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  size_t count;
  std::vector<std::unordered_multiset<int>> in;
  std::vector<std::unordered_multiset<int>> out;

};

#endif //CSETGRAPH_H
