#include "bits/stdc++.h"

using std::queue;
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

  void DFS();
  void BFS();

  bool Find(T value) const;
  void Insert(T value);
  bool Delete(T value);
  const T &FindMinimum() const;

 private:
  Node<T> *root;

  void dfs(Node<T> *node);
  void bfs(Node<T> *root);

  void deleter(Node<T> *node);

  Node<T> *find(Node<T> *node, T value);
  void insert(Node<T> *&node, T value);
  bool delete_(Node<T> *&node, T value);
  void deleteNode(Node<T> *&node);
};

template<class T>
BST<T>::BST(): root(nullptr) {};

template<class T>
BST<T>::~BST() {
  cout << "KEEEK";
  deleter(root);
};

template<class T>
void BST<T>::deleter(Node<T> *node) {
  if (node == nullptr)
    return;
  deleter(node->Left);
  deleter(node->Right);
  delete node;
};

template<class T>
void BST<T>::DFS() { dfs(root); };

template<class T>
void BST<T>::dfs(Node<T> *node) {
  if (node == nullptr)
    return;
  dfs(node->Left);
  dfs(node->Right);
  //TODO: visit( node );
};

template<class T>
void BST<T>::BFS() { bfs(root); };

template<class T>
void BST<T>::bfs(Node<T> *root) {
  if (root == nullptr) {
    return;
  }
  queue<Node<T> *> q;
  q.push(root);
  while (!q.empty()) {
    Node<T> *node = q.front();
    q.pop();
    cout << node->Data << " ";
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
  if (node == nullptr)
    return nullptr;
  if (node->Data == value)
    return node;
  if (node->Data > value)
    return find(node->Left, value);
  else
    return find(node->Right, value);
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
void BST<T>::Insert(T value) { insert(root, value); };

template<class T>
void BST<T>::insert(Node<T> *&node, T value) {
  if (node == NULL) {
    node = new Node<T>;
    node->Data = value;
    return;
  }
  if (node->Data > value)
    insert(node->Left, value);
  else
    insert(node->Right, value);
};

template<class T>
bool BST<T>::Delete(T value) { return delete_(root, value); };

template<class T>
bool BST<T>::delete_(Node<T> *&node, T value) {
  if (node == 0)
    return false;
  if (node->Data == value) {
    deleteNode(node);
    return true;
  }
  return delete_(node->Data > value ?
                 node->Left : node->Right, value);
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
    (minParent->Left == min ? minParent->Left : minParent->Right)
        = min->Right;
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

  tree.BFS();

  return 0;
}


