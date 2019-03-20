#include "bits/stdc++.h"

#define BASE 256

/*

  Дан массив строк. Количество строк не больше 100000.
  Отсортировать массив методом поразрядной сортировки MSD по символам.
  Размер алфавита - 256 символов. Последний символ строки = ‘\0’.

 */

using std::string;
using std::cin;
using std::cout;
using std::endl;

template<class T>
class Vector {
 public:
  Vector();
  ~Vector();

  void push_back(const T &data);

  T at(size_t index) const;
  T &operator[](size_t index);
  const T &operator[](size_t index) const;

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




void radix_sort(string *A, int from, int to, int d) {
  if (from >= to - 1)
    return;

  int *cnt = new int[BASE];

  for (int j = 0; j < BASE; j++) {
    cnt[j] = 0;
  }

  for (int i = from; i < to; i++) {
    int j = A[i][d];
    cnt[j]++;
  }

  for (int j = 1; j < BASE; j++) {
    cnt[j] += cnt[j - 1];
  }

  string *temp = new string[to - from];

  for (int i = to - 1; i >= from; i--) {
    int j = A[i][d];
    temp[--cnt[j]] = A[i];
  }

  for (int i = from; i < to; i++) {
    A[i] = temp[i - from];
  }

  delete[] temp;

  for (int i = 2; i < BASE; i++) {
    if (cnt[i - 1] - cnt[i])
      radix_sort(A, from + cnt[i - 1], from + cnt[i], d + 1);
  }


  delete[] cnt;
}




template<class T>
void radix_sort(Vector<T> &source, int from, int to, int d) {

  if (to - from <= 1)
    return;


  int *counter = new int[BASE];

  for (int j = 0; j < BASE; j++) {
    counter[j] = 0;
  }

  for (int i = from; i < to; i++) {
    int j = source[i][d];
    counter[j]++;
  }

  for (int j = 1; j < BASE; j++) {
    counter[j] += counter[j - 1];
  }

  string *temp = new string[to - from];

  for (int i = to - 1; i >= from; i--) {
    int j = source[i][d];
    temp[--counter[j]] = source[i];
  }

  for (int i = from; i < to; i++) {
    source[i] = temp[i - from];
  }

  delete[] temp;

  for (int i = 2; i < BASE; i++) {
    if (counter[i - 1] - counter[i])
      radix_sort(source, from + counter[i - 1], from + counter[i], d + 1);
  }

  delete[] counter;
}

int main() {
  int n = 0;

  Vector<string> source;

  while (!cin.eof()) {
    string temp;
    cin >> temp;
    source.push_back(temp);
    n++;
  }

  radix_sort(source, 0, n - 1, 0);

  for (int i = 0; i < n - 1; i++) {
    cout << source[i] << endl;
  }

  return 0;
}