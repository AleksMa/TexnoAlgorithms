#include <bits/stdc++.h>
using namespace std;

template<typename T>
class AVL {

 public:
  struct node {
    int balance;
    unsigned char height;
    T v;
    node *parent;
    node *left;
    node *right;
  };
  AVL();
  bool empty();
  T extractMin();
  T extractMax();


  void deleteNode(node *X);
  node *binaryInsert(T v);
  node *insert(T v);
  node *insert(node *p, T v);
  void replaceNode(node *X, node *Y);
  node *succ(node *X);
  node *prec(node *X);
  node *minimum(node *Y);
  node *maximum(node *Y);
  void deleteEverything();
  void delette(node *Y);


  node *rotateLeft(node *p);
  node *rotateRight(node *p);
  node *balance(node *p);


  void newDeleteNode(node *Y);


 private:

  unsigned char height(node *p) { return p ? p->height : 0; }
  int bfactor(node *p) { return height(p->right) - height(p->left); }

  void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = max(hl, hr) + 1;
  }

  node *root;
  node arr[N];
  int count;
};

template<typename T>
AVL<T>::AVL() {
  root = nullptr;
  count = 0;
}

template<typename T>
bool AVL<T>::empty() {
  return root == nullptr;
}

template<typename T>
typename AVL<T>::node *AVL<T>::minimum(node *Y) {
  if (Y == NULL)
    return NULL;
  node *X = Y;
  while (X->left != NULL) {
    X = X->left;
  }
  return X;
}

template<typename T>
typename AVL<T>::node *AVL<T>::maximum(node *Y) {
  if (Y == NULL)
    return NULL;
  node *X = Y;
  while (X->right != NULL) {
    X = X->right;
  }
  return X;
}

//Получение и удаление наименьшего элемента
template<typename T>
T AVL<T>::extractMin() {
  node *X = root;
  while (X->left != NULL) {
    X = X->left;
  }
  T t = X->v;
  newDeleteNode(X);
  return t;
}

//Получение и удаление наибольшего элемента
template<typename T>
T AVL<T>::extractMax() {
  node *X = root;
  while (X->right != NULL) {
    X = X->right;
  }
  T t = X->v;
  newDeleteNode(X);
  return t;
}

template<typename T>
typename AVL<T>::node *AVL<T>::succ(node *X) {
  if (X->right != NULL) {
    return minimum(X->right);
  }
  node *Y = X->parent;
  while (Y != NULL && X == Y->right) {
    X = Y;
    Y = Y->parent;
  }
  return Y;
}

template<typename T>
typename AVL<T>::node *AVL<T>::binaryInsert(T v) {
  node *Y;
  Y = &arr[count++];
  //Y = (node*)malloc(sizeof(node));
  Y->v = v;
  Y->parent = Y->left = Y->right = NULL;
  if (root == NULL)
    root = Y;
  else {
    node *X = root;
    while (1) {
      if (v < X->v) {
        if (X->left == NULL) {
          X->left = Y;
          Y->parent = X;
          break;
        }
        X = X->left;
      } else {
        if (X->right == NULL) {
          X->right = Y;
          Y->parent = X;
          break;
        }
        X = X->right;
      }
    }
  }
  return root;
}

//Добавление элемента
template<typename T>
typename AVL<T>::node *AVL<T>::insert(T v) {
  return insert(root, v);
}

template<typename T>
typename AVL<T>::node *insert(typename AVL<T>::node *p, T k) {
  if (!p) return new typename AVL<T>::node(k);
  if (k < p->key)
    p->left = insert(p->left, k);
  else
    p->right = insert(p->right, k);
  return balance(p);
}

//Вспомогательные функции для балансирования дерева
template<typename T>
void AVL<T>::replaceNode(node *X, node *Y) {
  if (X == root) {
    root = Y;
    if (Y != NULL) {
      Y->parent = NULL;
    }
  } else {
    node *P = X->parent;
    if (Y != NULL) {
      Y->parent = P;
    }
    if (P->left == X) {
      P->left = Y;
    } else {
      P->right = Y;
    }
  }
}

template<typename T>
void AVL<T>::newDeleteNode(node *Y) {

  int balanceDelta;
  node *X;
  node *Z = root;
  if (Z->left && Z->right) {
    node *W = Z->right;
    while (W->left)
      W = W->left;
    if (W->parent == Z) {
      Y = W;
      balanceDelta = -1;
    } else {
      Y = W->parent;
      balanceDelta = 1;
    }
    this->replaceNode(W, W->right);

    W->left = Z->left;
    Z->left->parent = W;
    W->right = Z->right;
    if (Z->right)
      Z->right->parent = W;
    replaceNode(Z, W);
  } else {
    X = Z->parent;
    balanceDelta = (X != NULL && Y == X->left ? 1 : -1);
    if (!Z->left && !Z->right)
      replaceNode(Z, NULL);
    else if (!Z->left)
      this->replaceNode(Z, Z->right);
    else if (!Z->right)
      replaceNode(Z, Z->left);
  }

  while (Y) {
    Y->balance += balanceDelta;

    node *X = Y->parent;
    balanceDelta = (X != NULL && Y == X->left ? 1 : -1);
    if (Y->balance == 2) {
      if (Y->right->balance == -1)
        rotateRight(Y->right);
      rotateLeft(Y);
      if (Y->balance == 1)
        return;
      break;
    } else if (Y->balance == -2) {
      if (Y->right->balance == 1)
        rotateLeft(Y->left);
      rotateRight(Y);
      if (Y->balance == -1)
        return;
      break;
    } else if (Y->balance == -1 || Y->balance == 1)
      return;
    Y = X;
  }

  //free(X);
}

template<typename T>
void AVL<T>::deleteNode(node *X) {
  if (X->left == NULL && X->right == NULL) {
    node *Z = X;
    while (Z != root) {
      Z = Z->parent;
    }
    replaceNode(X, NULL);
  } else if (X->left == NULL) {
    node *Z = X;
    while (Z != root) {
      Z = Z->parent;
    }
    replaceNode(X, X->right);
  } else if (X->right == NULL) {
    node *Z = X;
    while (Z != root) {
      Z = Z->parent;
    }
    replaceNode(X, X->left);
  } else {
    node *Y = succ(X);
    node *Z = Y;
    while (Z != root) {
      Z = Z->parent;
    }
    replaceNode(Y, Y->right);
    X->left->parent = Y;
    Y->left = X->left;
    if (X->right != NULL) {
      X->right->parent = Y;
    }
    Y->right = X->right;
    replaceNode(X, Y);
  }
  //free(X);
}

template<typename T>
typename AVL<T>::node *AVL<T>::rotateLeft(node *p) {
  node* q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

template<typename T>
typename AVL<T>::node *AVL<T>::rotateRight(node *p) {
  node *q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

template<typename T>
typename AVL<T>::node *AVL<T>::balance(node *p) {
  fixheight(p);
  if (bfactor(p) == 2) {
    if (bfactor(p->right) < 0)
      p->right = rotateright(p->right);
    return rotateleft(p);
  }
  if (bfactor(p) == -2) {
    if (bfactor(p->left) > 0)
      p->left = rotateleft(p->left);
    return rotateright(p);
  }
  return p;
}

//Очищение памяти
template<typename T>
void AVL<T>::deleteEverything() {
  delette(root);
  //delete arr;
}

template<typename T>
void AVL<T>::delette(node *Y) {
  if (Y != NULL) {
    delette(Y->left);
    delette(Y->right);
    free(Y);
  }
}

