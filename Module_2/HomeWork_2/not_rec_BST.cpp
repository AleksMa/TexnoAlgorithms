/*
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.
 Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).
 */

#include "bits/stdc++.h"

using std::queue;
using std::stack;
using std::cin;
using std::cout;




template<class T>
struct Node {
  Node() : Left(nullptr), Right(nullptr) {}
  Node(const T &data) : Data(data), Left(nullptr), Right(nullptr) {}

  T Data;
  Node *Left;
  Node *Right;
};

template<class T>
class BST {
 public:
  BST();
  ~BST();


  void write() { BFS(output); };

  bool Find(T value) const;
  void Insert(T value);
  bool Delete(T value);
  const T &FindMinimum() const;

 private:
  Node<T> *root;


  void DFS(void (*func)(Node<T> *));
  void preDFS(void (*func)(Node<T> *));
  void postDFS(void (*func)(Node<T> *));
  void BFS(void (*func)(Node<T> *));

  void dfs(Node<T> *node, void (*func)(Node<T> *));
  void pre_dfs(Node<T> *node, void (*func)(Node<T> *));
  void post_dfs(Node<T> *node, void (*func)(Node<T> *));
  void bfs(Node<T> *root, void (*func)(Node<T> *));

  static void output(Node<T> *node) { cout << node->Data << " "; }
  static void gcn(Node<T> *node) { delete node; }

  //void gc(root<T> *node);

  Node<T> *find(Node<T> *node, T value);
  //void insert(root<T> const *&node, T value);
  //bool delete_(root<T> *&node, T value);
  void deleteNode(Node<T> *&node);
};

template<class T>
BST<T>::BST(): root(nullptr) {};

template<class T>
BST<T>::~BST() {
  DFS(gcn);
};

template<class T>
void BST<T>::DFS(void (*func)(Node<T> *)) { dfs(root, func); };

template<class T>
void BST<T>::dfs(Node<T> *node, void (*func)(Node<T> *node)) {
  if (node == nullptr)
    return;
  //dfs(node->Left, func);
  //dfs(node->Right, func);
  //func(node);

  //In-order
  stack<Node<T> *> S;
  while (true) {
    while (node != nullptr) {
      S.push(node);
      node = node->Left;
    }
    if (S.empty())
      return;
    node = S.top();
    S.pop();
    func(node);
    node = node->Right;
  }

};

template<class T>
void BST<T>::preDFS(void (*func)(Node<T> *)) { pre_dfs(root, func); };

template<class T>
void BST<T>::pre_dfs(Node<T> *node, void (*func)(Node<T> *node)) {
  if (node == nullptr)
    return;
  //dfs(node->Left, func);
  //dfs(node->Right, func);
  //func(node);

  //Pre-order
  stack<Node<T> *> S;
  while (true) {
    while (node != nullptr) {
      func(node);
      S.push(node);
      node = node->Left;
    }
    if (S.empty())
      return;
    node = S.top();
    S.pop();
    node = node->Right;
  }

};

template<class T>
void BST<T>::postDFS(void (*func)(Node<T> *)) { post_dfs(root, func); };

template<class T>
void BST<T>::post_dfs(Node<T> *node, void (*func)(Node<T> *node)) {
  if (node == nullptr)
    return;
  //dfs(node->Left, func);
  //dfs(node->Right, func);
  //func(node);
  Node<T> *peek_node = nullptr, *last_visited_node = nullptr;
  //Post-order
  stack<Node<T> *> S;
  while (true) {
    while (node != nullptr) {
      S.push(node);
      node = node->Left;
    }

    if(S.empty())
      return;

    peek_node = S.top();
    if (peek_node->Right != nullptr && last_visited_node != peek_node->Right)
      node = peek_node->Right;
    else {
      S.pop();
      func(peek_node);
      last_visited_node = peek_node;
    }
  }
};

template<class T>
void BST<T>::BFS(void (*func)(Node<T> *node)) { bfs(root, func); };

template<class T>
void BST<T>::bfs(Node<T> *root, void (*func)(Node<T> *node)) {
  if (root == nullptr) {
    return;
  }
  queue<Node<T> *> q;
  q.push(root);
  while (!q.empty()) {
    Node<T> *node = q.front();
    q.pop();

    func(node);

    if (node->Left != nullptr)
      q.push(node->Left);
    if (node->Right != nullptr)
      q.push(node->Right);
  }
};

template<class T>
bool BST<T>::Find(T value) const { return find(root, value) != nullptr; };

template<class T>
Node<T> *BST<T>::find(Node<T> *node, T value) {
  while (true) {
    if (node == nullptr)
      return nullptr;
    if (node->Data == value)
      return node;
    if (node->Data > value)
      node = node->Left;
    else
      node = node->Right;
  }
};

template<class T>
const T &BST<T>::FindMinimum() const {
  Node<T> *node = root;
  assert(node != nullptr);
  while (node->Left != nullptr)
    node = node->Left;
  return node->Data;
};

template<class T>
void BST<T>::Insert(T value) {
  Node<T> **node = &root;

  while (true) {
    if (*node == nullptr) {
      *node = new Node<T>(value);
      return;
    }
    if ((*node)->Data > value)
      node = &(*node)->Left;
    else
      node = &(*node)->Right;
  }
};

template<class T>
bool BST<T>::Delete(T value) {
  Node<T> **node = &root;

  while (true) {
    if (*node == nullptr)
      return false;
    if ((*node)->Data == value) {
      deleteNode(*node);
      return true;
    }
    if ((*node)->Data > value)
      node = &(*node)->Left;
    else
      node = &(*node)->Right;
  }
};

template<class T>
void BST<T>::deleteNode(Node<T> *&node) {
  if (node->Left == 0) {
    Node<T> *right = node->Right;
    delete node;
    node = right;
  } else if (node->Right == 0) {
    Node<T> *left = node->Left;
    delete node;
    node = left;
  } else {
    Node<T> *minParent = node;
    Node<T> *min = node->Right;
    while (min->Left != 0) {
      minParent = min;
      min = min->Left;
    }
    node->Data = min->Data;
    if (minParent->Left == min)
      minParent->Left = min->Right;
    else
      minParent->Right = min->Right;

    delete min;
  }
}

int main() {
  int N = 0, a = 0;
  BST<int> tree;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;
    tree.Insert(a);
  }

  tree.write();

  return 0;
}


