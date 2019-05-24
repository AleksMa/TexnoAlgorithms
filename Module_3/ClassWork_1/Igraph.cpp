#include "bits/stdc++.h"

using std::vector;

struct IGraph {
  virtual ~IGraph() {}

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const = 0;

  virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int count);
    ListGraph(const IGraph &graph);

    virtual ~ListGraph();
    virtual void AddEdge(int from, int to);
    virtual int VerticesCount() const;
    virtual std::vector<int> GetNextVertices(int vertex) const;
    virtual std::vector<int> GetPrevVertices(int vertex) const;

private:
    vector<vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int count) {
    adjacencyLists.resize(count);
}

ListGraph::ListGraph(const IGraph &graph) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacencyLists.push_back(graph.GetNextVertices(i));
    }
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to) {
    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const {
    vector<int> next;
    for (int i = 0; i < adjacencyLists[vertex].size(); ++i) {
        next.push_back(adjacencyLists[vertex][i]);
    }
    return next;
}

vector<int> ListGraph::GetPrevVertices(int vertex) const {
    vector<int> prev;
    for (int i = 0; i < adjacencyLists.size(); ++i) {
        for (int j = 0; j < adjacencyLists[j].size(); ++j) {
            if (adjacencyLists[i][j] == vertex) {
                prev.push_back(i);
            }
        }
    }
    return prev;
}

void BFS(const IGraph &graph, int vertex, void (*visit)(int)){
    vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while(qu.size() != 0){
        int current = qu.front();
        qu.pop();
        visit(current);
        vector<int> adjacencyVertices = graph.GetNextVertices(current);
        for (int i = 0; i < adjacencyVertices.size(); ++i) {
            if(!visited[adjacencyVertices[i]]) {
                qu.push(adjacencyVertices[i]);
                visited[adjacencyVertices[i]] = true;
            }
        }
    }
}

int main() {
    ListGraph g(5);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 3);
    g.AddEdge(1, 4);
    g.AddEdge(2, 4);
    g.AddEdge(3, 4);
    g.AddEdge(2, 3);
    g.AddEdge(2, 1);
    BFS(g, 0, [](int a){std::cout << a << " ";});
    return 0;
};