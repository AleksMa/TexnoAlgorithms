#include <bits/stdc++.h>
using namespace std;

template<typename T>
class AVL {

 public:

  AVL();
  ~AVL();
  bool empty();
  //T extractMin();
  //T extractMax();

  void write() { BFS(output); };

  bool insert(T v);

  bool Delete(T value);


 private:

  struct Node {
    Node() : Left(nullptr), Right(nullptr) {}
    Node(const T &data) : Data(data), Left(nullptr), Right(nullptr), height(0) {}

    unsigned char height;
    T Data;
    Node *Left;
    Node *Right;
  };

  Node *insert(Node *p, T v);

  void DFS(void (*func)(Node *));
  void BFS(void (*func)(Node *));

  void dfs(Node *node, void (*func)(Node *));
  void bfs(Node *root, void (*func)(Node *));

  Node *rotateLeft(Node *p);
  Node *rotateRight(Node *p);
  Node *balance(Node *p);

  bool delete_(Node *&p, T value);
  void deleteNode(Node *&p);

  static void output(Node *p) { cout << p->Data << " "; }
  static void gcn(Node *p) { delete p; }

  unsigned char height(Node *p) { return p ? p->height : 0; }
  int bfactor(Node *p) { return height(p->Right) - height(p->Left); }

  void fixheight(Node *p) {
    unsigned char hl = height(p->Left);
    unsigned char hr = height(p->Right);
    p->height = max(hl, hr) + 1;
  }

  Node *root;
};

template<typename T>
AVL<T>::AVL() {
  root = nullptr;
}

template<class T>
AVL<T>::~AVL() {
  DFS(gcn);
};

template<class T>
void AVL<T>::DFS(void (*func)(Node *)) { dfs(root, func); };

template<class T>
void AVL<T>::dfs(Node *node, void (*func)(Node *node)) {
  if (node == nullptr)
    return;
  dfs(node->Left, func);
  dfs(node->Right, func);
  func(node);

};

template<class T>
void AVL<T>::BFS(void (*func)(Node *node)) { bfs(root, func); };

template<class T>
void AVL<T>::bfs(Node *root, void (*func)(Node *node)) {
  if (root == nullptr) {
    return;
  }
  queue<Node *> q;
  q.push(root);
  q.push(nullptr);
  while (q.size() > 1) {
    Node *node = q.front();
    q.pop();

    if (node == nullptr) {
      cout << "\n";
      q.push(nullptr);
      continue;
    }

    func(node);

    if (node->Left != nullptr)
      q.push(node->Left);
    if (node->Right != nullptr)
      q.push(node->Right);
  }
};

template<typename T>
bool AVL<T>::empty() {
  return root == nullptr;
}

template<typename T>
bool AVL<T>::insert(T v) {
  if (!root) {
    root = new Node(v);
    return true;
  }
  Node *t = insert(root, v);
  return t != nullptr;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::insert(Node *p, T v) {
  if (!p) return new Node(v);
  if (v < p->Data)
    p->Left = insert(p->Left, v);
  else
    p->Right = insert(p->Right, v);
  return balance(p);
}

template<typename T>
typename AVL<T>::Node *AVL<T>::rotateLeft(Node *q) {
  Node* p = q->Right;
  q->Right = p->Left;
  p->Left = q;
  fixheight(q);
  fixheight(p);
  return p;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::rotateRight(Node *p) {
  Node *q = p->Left;
  p->Left = q->Right;
  q->Right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

template<typename T>
typename AVL<T>::Node *AVL<T>::balance(Node *p) {
  if(!p)
    return nullptr;
  fixheight(p);
  if (bfactor(p) == 2) {
    if (bfactor(p->Right) < 0)
      p->Right = rotateRight(p->Right);
    return rotateLeft(p);
  }
  if (bfactor(p) == -2) {
    if (bfactor(p->Left) > 0)
      p->Left = rotateLeft(p->Left);
    return rotateRight(p);
  }
  return p;
}

template<class T>
bool AVL<T>::Delete(T value) { return delete_(root, value); };

template<class T>
bool AVL<T>::delete_(Node *&p, T value) {
  if (p == nullptr)
    return false;
  if (p->Data == value) {
    deleteNode(p);
    return true;
  }
  Node *&del_node = (p->Data > value ? p->Left : p->Right);
  //bool fl = del_node == nullptr || (del_node->Data == value && del_node->Right == nullptr && del_node->Left == nullptr);
  bool t = delete_(del_node, value);
  //if(!fl && t)
    balance(del_node);
  return t;
};

template<class T>
void AVL<T>::deleteNode(Node *&node) {
  if (node->Left == 0) {
    Node *right = node->Right;
    delete node;
    node = right;
  } else if (node->Right == 0) {
    Node *left = node->Left;
    delete node;
    node = left;
  } else {
    Node *minParent = node;
    Node *min = node->Right;
    while (min->Left != 0) {
      minParent = min;
      min = min->Left;
    }
    node->Data = min->Data;
    (minParent->Left == min ? minParent->Left : minParent->Right) = min->Right;
    delete min;
  }
}

int main() {

  int N = 0, a = 0;
  AVL<int> tree;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;
    tree.insert(a);
  }

  tree.write();

  return 0;
}


/*
 *
 *
 */