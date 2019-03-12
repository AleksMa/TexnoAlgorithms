#include "bits/stdc++.h"

/*
 *
 * Вовочка ест фрукты из бабушкиной корзины.
 * В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм.
 * Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
 * которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину.
 * Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.
 *
 */


template<class T>
class Vector {
 public:
  Vector();
  ~Vector();

  void push_back(const T &data);
  void erase_back();

  T at(size_t index) const;
  T &operator[](size_t index);
  T &last();
  const T &operator[](size_t index) const;

  size_t size() const;
  size_t capacity() const;

  bool empty();

 private:
  T *buffer;
  size_t buffer_size;
  size_t len;

  void grow();
};

template<class T>
bool Vector<T>::empty() {
  return len == 0;
}

template<class T>
T &Vector<T>::last() {
  assert(buffer != 0 && len > 0);
  return buffer[len - 1];
}

template<class T>
Vector<T>::Vector():buffer(0), buffer_size(0), len(0) {}

template<class T>
Vector<T>::~Vector() { delete[] buffer; }

template<class T>
size_t Vector<T>::size() const { return len; }

template<class T>
T Vector<T>::at(size_t index) const {
  assert(index >= 0 && index < len && buffer != 0);
  return buffer[index];
}

template<class T>
const T &Vector<T>::operator[](size_t index) const {
  assert(index >= 0 && index < len && buffer != 0);
  return buffer[index];
}

template<class T>
T &Vector<T>::operator[](size_t index) {
  assert(index >= 0 && index < len && buffer != 0);
  return buffer[index];
}

template<class T>
void Vector<T>::grow() {
  size_t new_buffer_size = (buffer_size ? buffer_size * 2 : 1);
  T *new_buffer = new T[new_buffer_size];
  for (int i = 0; i < len; i++)
    new_buffer[i] = buffer[i];
  delete[] buffer;
  buffer = new_buffer;
  buffer_size = new_buffer_size;
}

template<class T>
void Vector<T>::push_back(const T &data) {
  if (len == buffer_size)
    grow();
  assert(len < buffer_size && buffer != 0);
  buffer[len++] = data;
}

template<class T>
void Vector<T>::erase_back() {
  assert(len > 0 && buffer != 0);
  len--;
}

template<class T>
class Heap {
 public:
  Heap();
  Heap(Vector<T> V, size_t n);

  void Insert(T element);

  T ExtractMax();

  const T &PeekMax() const;

 private:
  Vector<T> buff;

  void buildHeap();
  void siftDown(int i);
  void siftUp(int i);

};

template<class T>
const T &Heap<T>::PeekMax() const {
  return buff[0];
}

template<class T>
Heap<T>::Heap() {}

template<class T>
Heap<T>::Heap(Vector<T> V, size_t n) {
  assert(V.size() == n);
  for (size_t i = 0; i < n; i++) {
    buff.push_back(V[i]);
  }
  buildHeap();
}

template<class T>
void Heap<T>::siftDown(int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if (left < buff.size() && buff[left] > buff[i])
    largest = left;
  if (right < buff.size() && buff[right] > buff[largest])
    largest = right;
  if (largest != i) {
    std::swap(buff[i], buff[largest]);
    siftDown(largest);
  }
}

template<class T>
void Heap<T>::buildHeap() {
  for (int i = buff.size() / 2 - 1; i >= 0; --i) {
    siftDown(i);
  }
}

template<class T>
void Heap<T>::siftUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (buff[index] <= buff[parent])
      return;
    std::swap(buff[index], buff[parent]);
    index = parent;
  }
}

template<class T>
void Heap<T>::Insert(T element) {
  buff.push_back(element);
  siftUp(buff.size() - 1);
}

template<class T>
T Heap<T>::ExtractMax() {
  assert(!buff.empty());
  int result = buff[0];
  buff[0] = buff.last();
  buff.erase_back();
  if (!buff.empty()) {
    siftDown(0);
  }
  return result;
}

int main(int argc, char **argv) {

  Vector<int> V;
  int k = 5;

  V.push_back(5);

  V.push_back(228);

  V.push_back(8);

  V.push_back(5);

  Heap<int> Q(V, k - 1);

  

}






