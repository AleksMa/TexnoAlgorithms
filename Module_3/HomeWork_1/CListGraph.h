#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H

#include <iostream>
#include <list>
#include "IGraph.h"

class CListGraph : public IGraph {
 public:
  CListGraph(unsigned int v_count);
  CListGraph(const IGraph *graph);

  virtual void AddEdge(int from, int to) override;
  virtual int VerticesCount() const override;
  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  size_t count;
  std::vector<std::list<int>> in;
  std::vector<std::list<int>> out;

};

#endif //CLISTGRAPH_H
