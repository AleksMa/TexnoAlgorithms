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