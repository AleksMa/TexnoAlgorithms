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
class Stack {
 public:
  Stack();

  void push(const T &data);
  void pop();                       // Сохраняя традиции stl - pop не возвращает значение (только убирает с вершины)
  const T &top() const;                    // top не убирает значение с вершины  (только возвращает)

  size_t size() const;
  bool empty() const;

 private:
  Vector<T> V;
  size_t stack_top;

};

template<class T>
Stack<T>::Stack():stack_top(0) {}

template<class T>
void Stack<T>::push(const T &data) {
  if (stack_top
      == V.size()) {      // Если массив переполнен или следующее значение не инициализровано - делегируем добавление элемента вектору
    V.push_back(data);
  } else {
    V[stack_top] = data;            // В противном случае имеем право присвоить значение
  }
  stack_top++;
}

template<class T>
void Stack<T>::pop() {
  assert(!empty());
  stack_top--;
}

template<class T>
const T &Stack<T>::top() const {
  assert(!empty());
  return V[stack_top - 1];
};

template<class T>
size_t Stack<T>::size() const {
  return stack_top;
}

template<class T>
bool Stack<T>::empty() const {
  return stack_top == 0;
}



template<class T>
class PriorityQueue {
 public:
  PriorityQueue();
  PriorityQueue(const T* V, size_t n);

  void insert(const T& element);

  T extract_max();
  const T &peek_max();

  size_t size();
  bool empty();

 private:
  Vector<T> buff;

  void build_heap();
  void sift_down(int i);
  void sift_up(int i);

};

template<class T>
PriorityQueue<T>::PriorityQueue() {}

template<class T>
PriorityQueue<T>::PriorityQueue(const T* V, size_t n) {
  assert(V);
  for (size_t i = 0; i < n; i++) {
    buff.push_back(V[i]);
  }
  build_heap();
}

template<class T>
void PriorityQueue<T>::insert(const T& element) {
  buff.push_back(element);
  sift_up(buff.size() - 1);
}

template<class T>
T PriorityQueue<T>::extract_max() {
  assert(!buff.empty());
  int result = buff[0];
  buff[0] = buff.last();
  buff.erase_back();
  if (!buff.empty()) {
    sift_down(0);
  }
  return result;
}

template<class T>
const T &PriorityQueue<T>::peek_max() {
  assert(!buff.empty());
  return buff[0];
}

template<class T>
bool PriorityQueue<T>::empty() {
  return buff.empty();
}

template<class T>
size_t PriorityQueue<T>::size() {
  return buff.size();
}

template<class T>
void PriorityQueue<T>::sift_down(int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if (left < buff.size() && buff[left] > buff[i])
    largest = left;
  if (right < buff.size() && buff[right] > buff[largest])
    largest = right;
  if (largest != i) {
    std::swap(buff[i], buff[largest]);
    sift_down(largest);
  }
}

template<class T>
void PriorityQueue<T>::sift_up(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (buff[index] <= buff[parent])
      return;
    std::swap(buff[index], buff[parent]);
    index = parent;
  }
}

template<class T>
void PriorityQueue<T>::build_heap() {
  for (int i = (int) buff.size() / 2 - 1; i >= 0; --i) {
    sift_down(i);
  }
}


int eater(int *source, int n, int K){
  int count = 0, acc = 0, curr = 0;
  PriorityQueue<int> Q(source, n);
  Stack<int> S;

  while (!Q.empty()) {
    while (!Q.empty()) {
      curr = Q.peek_max();
      if (curr + acc > K)
        break;
      curr = Q.extract_max();
      acc += curr;
      curr /= 2;
      if (curr)
        S.push(curr);
    }

    while (!S.empty()) {
      curr = S.top();
      S.pop();

      Q.insert(curr);
    }

    acc = 0;
    count++;
  }

  return count;
}


int main(int argc, char **argv) {
  int n = 0, K = 0, temp = 0;

  std::cin >> n;

  int *arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> temp;
    arr[i] = temp;
  }

  std::cin >> K;

  std::cout << eater(arr, n, K);


  delete[] arr;

}






