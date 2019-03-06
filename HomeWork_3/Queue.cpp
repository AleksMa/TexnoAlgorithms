#include "bits/stdc++.h"

/*
 * Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 * Обрабатывать команды push back и pop front.
 */



//Сразу реализуем свой динамический массив (вектор) для использования в стеке
template<class T>
class Vector {
 public:
  Vector();
  ~Vector();

  void push_back(const T &data);

  T at(size_t index) const;
  T &operator[](size_t index);
  const T& operator[](size_t index) const;

  size_t size() const;
  size_t capacity() const;

 private:
  T *buffer;
  size_t buffer_size;
  size_t len;

  void grow();
};

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
const T& Vector<T>::operator[](size_t index) const {
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
size_t Vector<T>::capacity() const { return buffer_size; };


// Реализация стека через динамический массив
// Делегирует часть функций вектору


template<class T>
class Stack {
 public:
  Stack();

  void push(const T &data);
  void pop();                       // Сохраняя традиции stl - pop не возвращает значение (только убирает с вершины)
  const T& top() const;                    // top не убирает значение с вершины  (только возвращает)

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
const T& Stack<T>::top() const {
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


// Реализация очереди через два стека
// Делегирует почти все функции стеку

template<class T>
class Queue {
 public:

  void enqueue(T &data);                // Положить элемент в очередь
  T dequeue();                          // Взять элемент из очереди
  const T &top();                       // Посмотреть на первый элемент очереди

  size_t size() const;
  bool empty() const;

 private:
  Stack<T> S1, S2;

};

template<class T>
void Queue<T>::enqueue(T &data) {
  S1.push(data);                                // Приходящие элементы кладем в первый стек
}

template<class T>
T Queue<T>::dequeue() {                         // Берем элементы из второго стека - если он пуст, то перекидываем в него первый стек
  assert(!empty());
  T temp = top();
  S2.pop();
  return temp;
}

template<class T>
const T &Queue<T>::top() {
  assert(!empty());
  if (S2.empty()) {
    while (!S1.empty()) {
      S2.push(S1.top());
      S1.pop();
    }
  }
  return S2.top();
};

template<class T>
size_t Queue<T>::size() const {
  return S1.size() + S2.size();
}

template<class T>
bool Queue<T>::empty() const {
  return S1.empty() && S2.empty();
}

int main(int argc, char **argv) {

  Queue<int> Q;
  bool result = true;
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int command = 0;
    int data = 0;
    std::cin >> command >> data;
    switch (command) {
      case 2:
        if (Q.empty()) {
          result = (result && data == -1);
        } else {
          result = (result && Q.dequeue() == data);
        }
        break;
      case 3:Q.enqueue(data);
        break;
    }
  }

  std::cout << (result ? "YES" : "NO");

}