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





template<class T>
class Compare {
 public:
  bool operator()(const T &l, const T &r) {
    return l < r;
  }
};

void radix_sort(string *A, int from, int to, int d) {
  if(A[from].size() < d || from >= to - 1)
    return;

  //cout << d << ":\t" << from << "\t" << to << endl;

  int *cnt = new int[BASE];

  for(int j = 0; j < BASE; j++){
    cnt[j] = 0;
  }

  for(int i = from; i < to; i++){
    int j = A[i][d];
    cnt[j]++;
  }


  for(int j = 1; j < BASE; j++){
    cnt[j] += cnt[j - 1];
  }

  string *temp = new string[to - from];


  for(int i = to - 1; i >= from; i--){
    int j = A[i][d];
    temp[--cnt[j]] = A[i];
  }

  //memcpy(A + from, temp, (to - from) * sizeof(string));



  for(int i = from; i < to; i++){
    A[i] = temp[i - from];
  }

  //radix_sort(A, from, from + cnt[0] - 1, d + 1);

  for(int i = 1; i < BASE; i++){
    if(cnt[i - 1] - cnt[i])
      radix_sort(A, from + cnt[i - 1], from + cnt[i], d + 1);
  }



  delete[] temp;
  delete[] cnt;
}




int main() {
  int n = 0;

  Vector<string>V;

  while(!cin.eof()){
    string t;
    cin >> t;
    V.push_back(t);
    n++;
  }

  n--;

  string *arr = new string[n];

  for(int i = 0; i < V.size() - 1; i++){
    arr[i] = V[i];
  }

  radix_sort(arr, 0, n, 0);


  for(int i = 0; i < n; i++){
    cout << arr[i] << endl;

  }



  delete[] arr;

  return 0;
}