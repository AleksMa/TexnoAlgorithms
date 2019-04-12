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

  void DFS(void (*func)(Node<T> *));
  void preDFS(void (*func)(Node<T> *));
  void postDFS(void (*func)(Node<T> *));
  void BFS(void (*func)(Node<T> *));

  int max_width();

  bool Find(T value) const;
  void Insert(T value);
  bool Delete(T value);
  const T &FindMinimum() const;

 private:
  Node<T> *root;

  void dfs(Node<T> *node, void (*func)(Node<T> *));
  void pre_dfs(Node<T> *node, void (*func)(Node<T> *));
  void post_dfs(Node<T> *node, void (*func)(Node<T> *));
  void bfs(Node<T> *root, void (*func)(Node<T> *));

  Node<T> *find(Node<T> *node, T value);
  void deleteNode(Node<T> *&node);
};

template<class T>
BST<T>::BST(): root(nullptr) {};

template<class T>
void gcn(Node<T> *node) {
  delete node;
}

template<class T>
void output(Node<T> *node) {
  cout << node->Data << " ";
}

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
  Node<T> *peek_node = nullptr, *last_visited_node = nullptr;
  stack<Node<T> *> S;
  while (true) {
    while (node != nullptr) {
      S.push(node);
      node = node->Left;
    }

    if (S.empty())
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
  q.push(nullptr);
  while (q.size() > 1) {
    Node<T> *node = q.front();
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

template<class T>
int BST<T>::max_width() {
  if (root == nullptr) {
    return 0;
  }
  queue<Node<T> *> q;
  q.push(root);
  q.push(nullptr);
  int M = 0, t = 0;
  while (q.size() > 1) {
    Node<T> *node = q.front();
    q.pop();

    if (node == nullptr) {
      M = std::max(M, t);
      t = 0;
      q.push(nullptr);
      continue;
    }

    t++;

    if (node->Left != nullptr)
      q.push(node->Left);
    if (node->Right != nullptr)
      q.push(node->Right);
  }
  return M;
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

template<class T, class P>
struct TreapNode {
  TreapNode() : Left(nullptr), Right(nullptr) {}
  TreapNode(const T &data, const P &priority) : Data(data), Priority(priority) {};

  T Data;
  P Priority;
  TreapNode<T, P> *Left;
  TreapNode<T, P> *Right;
};

template<class T, class P>
class Treap {
 public:
  Treap();
  ~Treap();

  void DFS(void (*func)(TreapNode<T, P> *));
  void preDFS(void (*func)(TreapNode<T, P> *));
  void postDFS(void (*func)(TreapNode<T, P> *));
  void BFS(void (*func)(TreapNode<T, P> *));

  int max_width();

  bool Find(T value) const;
  void Insert(T value, P priority);
  bool Delete(T value);
  const T &FindMinimum() const;

 private:
  TreapNode<T, P> *root;

  void dfs(TreapNode<T, P> *node, void (*func)(TreapNode<T, P> *));
  void bfs(TreapNode<T, P> *root, void (*func)(TreapNode<T, P> *));

  void split(TreapNode<T, P> *currentNode, T key, TreapNode<T, P> *&left, TreapNode<T, P> *&right);
  TreapNode<T, P>* merge(TreapNode<T, P> *left, TreapNode<T, P> *right);

  TreapNode<T, P> *find(TreapNode<T, P> *node, T value);
  void deleteNode(TreapNode<T, P> *&node);
};

template<class T, class P>
Treap<T, P>::Treap(): root(nullptr) {};

template<class T, class P>
void gcn(TreapNode<T, P> *node) {
  delete node;
}

template<class T, class P>
void output(TreapNode<T, P> *node) {
  cout << node->Data << " ";
}

template<class T, class P>
Treap<T, P>::~Treap() {
  DFS(gcn);
};

template<class T, class P>
void Treap<T, P>::DFS(void (*func)(TreapNode<T, P> *)) { dfs(root, func); };

template<class T, class P>
void Treap<T, P>::dfs(TreapNode<T, P> *node, void (*func)(TreapNode<T, P> *node)) {
  if (node == nullptr)
    return;
  //dfs(node->Left, func);
  //dfs(node->Right, func);
  //func(node);

  //In-order
  stack<TreapNode<T, P> *> S;
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

template<class T, class P>
void Treap<T, P>::BFS(void (*func)(TreapNode<T, P> *node)) { bfs(root, func); };

template<class T, class P>
void Treap<T, P>::bfs(TreapNode<T, P> *root, void (*func)(TreapNode<T, P> *node)) {
  if (root == nullptr) {
    return;
  }
  queue<TreapNode<T, P> *> q;
  q.push(root);
  q.push(nullptr);
  while (q.size() > 1) {
    TreapNode<T, P> *node = q.front();
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

template<class T, class P>
int Treap<T, P>::max_width() {
  if (root == nullptr) {
    return 0;
  }
  queue<TreapNode<T, P> *> q;
  q.push(root);
  q.push(nullptr);
  int M = 0, t = 0;
  while (q.size() > 1) {
    TreapNode<T, P> *node = q.front();
    q.pop();

    if (node == nullptr) {
      M = std::max(M, t);
      t = 0;
      q.push(nullptr);
      continue;
    }

    t++;

    if (node->Left != nullptr)
      q.push(node->Left);
    if (node->Right != nullptr)
      q.push(node->Right);
  }
  return M;
};

template<class T, class P>
bool Treap<T, P>::Find(T value) const { return find(root, value) != nullptr; };

template<class T, class P>
TreapNode<T, P> *Treap<T, P>::find(TreapNode<T, P> *node, T value) {
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

template<class T, class P>
const T &Treap<T, P>::FindMinimum() const {
  TreapNode<T, P> *node = root;
  assert(node != nullptr);
  while (node->Left != nullptr)
    node = node->Left;
  return node->Data;
};

template<class T, class P>
void Treap<T, P>::Insert(T value, P priority) {

  TreapNode<T, P> *currentNode = root;
  while(currentNode != nullptr && currentNode->Priority >= priority){
    currentNode = (currentNode->Data > value ? currentNode->Left : currentNode->Right );
  }
  TreapNode<T, P> *T1 = nullptr, *T2 = nullptr;
  TreapNode<T, P> *newT = new TreapNode<T, P>(value, priority);
  split(root, value, T1, T2);
  TreapNode<T, P> *M = merge(T1, newT);
  root = merge(M, T2);
};

template<class T, class P>
bool Treap<T, P>::Delete(T value) {
  TreapNode<T, P> **node = &root;

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

template<class T, class P>
void Treap<T, P>::deleteNode(TreapNode<T, P> *&node) {
  if (node->Left == 0) {
    TreapNode<T, P> *right = node->Right;
    delete node;
    node = right;
  } else if (node->Right == 0) {
    TreapNode<T, P> *left = node->Left;
    delete node;
    node = left;
  } else {
    TreapNode<T, P> *minParent = node;
    TreapNode<T, P> *min = node->Right;
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

template<class T, class P>
void Treap<T, P>::split(TreapNode<T, P> *currentNode, T key, TreapNode<T, P> *&left,
           TreapNode<T, P> *&right) {
  if (currentNode == nullptr) {
    left = nullptr;
    right = nullptr;
  } else if (currentNode->Data <= key) {
    split(currentNode->Right, key, currentNode->Right, right);
    left = currentNode;
  } else {
    split(currentNode->Left, key, left, currentNode->Left);
    right = currentNode;
  }
}

template<class T, class P>
TreapNode<T, P>* Treap<T, P>::merge(TreapNode<T, P> *left, TreapNode<T, P> *right)
{
  if( left == 0 || right == 0 ) {
    return left == 0 ? right : left;
  }
  if( left->Priority > right->Priority ) {
    left->Right = merge(left->Right, right);
    return left;
  } else {
    right->Left = merge(left, right->Left);
    return right;
  }
}


int main() {
  int N = 0, a = 0, b = 0;
  BST<int> tree;
  Treap<int, int> treap;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    tree.Insert(a);
    treap.Insert(a, b);
  }

  tree.BFS(output);

  int wBST = tree.max_width(), wTreap = treap.max_width();

  cout << std::endl << "///" << wBST << std::endl;

  treap.BFS(output);

  cout << std::endl << "///" <<  wTreap << std::endl;

  cout << wTreap - wBST;

  return 0;
}


